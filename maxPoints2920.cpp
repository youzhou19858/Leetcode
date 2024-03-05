#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int maximumPoints(vector<vector<int>> &edges, vector<int> &coins, int k) {
    auto pHash = [](const auto &p) { return p.first; };
    auto pEqual = [](const auto &lhs, const auto &rhs) {
      return lhs.first == rhs.first;
    };
    using pSet =
        unordered_set<pair<int, int>, decltype(pHash), decltype(pEqual)>;
    auto comp = [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
      return lhs.second < rhs.second;
    };
    auto addNew = [](pSet &layer, const pair<int, int> p) {
      auto [it, inserted] = layer.insert(p);
      if (!inserted && it->second < p.second) {
        layer.erase(it);
        layer.insert(p);
      }
    };
    const int kN = coins.size();
    vector<unordered_set<int>> tree(kN, unordered_set<int>());
    for (const auto &edge : edges) {
      tree[edge[0]].insert(edge[1]);
      tree[edge[1]].insert(edge[0]);
    }
    auto getKid = [&tree](int node) {
      if (tree[node].empty()) {
        return 0;
      }
      auto it = tree[node].begin();
      int kid = *it;
      tree[node].erase(it);
      tree[kid].erase(node);
      return kid;
    };
    pSet choseF{{{0, coins[0] - k}}, 2, pHash, pEqual},
        choseS{{{1, coins[0] / 2}}, 2, pHash, pEqual};
    vector<int> stack{0};
    while (stack.size()) {
      for (int kid = getKid(stack.back()); kid;
           stack.push_back(kid), kid = getKid(kid)) {
        pSet nextChoseF{choseF.size() + choseS.size() + 16, pHash, pEqual},
            nextChoseS{choseF.size() + choseS.size() + 16, pHash, pEqual};
        for (const auto &[toR, points] : choseF) {
          addNew(nextChoseF, {toR, points + (coins[kid] >> min(31, toR)) - k});
          addNew(nextChoseS,
                 {toR + 1, points + (coins[kid] >> min(31, toR + 1))});
        }
        for (const auto &[toR, points] : choseS) {
          addNew(nextChoseF, {toR, points + (coins[kid] >> min(31, toR)) - k});
          addNew(nextChoseS,
                 {toR + 1, points + (coins[kid] >> min(31, toR + 1))});
        }
        choseF.swap(nextChoseF);
        choseS.swap(nextChoseS);
      }
      stack.pop_back();
      pSet prevChoseS{choseS.size(), pHash, pEqual};
      for (const auto &[toR, points] : choseS) {
        addNew(prevChoseS, {max(0, toR - 1), points});
      }
      choseS.swap(prevChoseS);
    }
    return max(max_element(choseF.begin(), choseF.end(), comp)->second,
               max_element(choseS.begin(), choseS.end(), comp)->second);
  }
};

int main() {
  Solution sol;
  vector<vector<int>> edges{{0, 1}, {0, 2}, {1, 3}, {3, 4}, {0, 5},
                            {6, 3}, {5, 7}, {3, 8}, {9, 7}};
  vector<int> coins{0, 5, 10, 5, 6, 5, 0, 2, 0, 0};
  int k = 7;
  cout << sol.maximumPoints(edges, coins, k) << endl;
}