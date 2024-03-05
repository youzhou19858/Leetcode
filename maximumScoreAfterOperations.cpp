#include "cppCommonHeaders.hpp"
class Solution {
 public:
  long long maximumScoreAfterOperations(vector<vector<int>>& edges,
                                        vector<int>& values) {
    vector<unordered_set<int>> tree(edges.size() + 1);
    for (const auto& edge : edges) {
      tree[edge[0]].insert(edge[1]);
      tree[edge[1]].insert(edge[0]);
    }
    auto getNextKid = [&](int p) {
      if (tree[p].empty()) {
        return 0;
      }
      int k = *tree[p].begin();
      tree[p].erase(k);
      tree[k].erase(p);
      return k;
    };
    vector<pair<int, unordered_set<int>>> pathToLeaf{};
    vector<int> st{0};
    int pathSum{values[0]};
    while (st.size()) {
      for (int k = getNextKid(st.back()); k; k = getNextKid(st.back())) {
        pathSum += values[k];
        st.push_back(k);
      }
      pathToLeaf.push_back({pathSum, {st.begin(), st.end()}});
      int k = getNextKid(st.back());
      while (!k) {
        pathSum -= values[st.back()];
        st.pop_back();
        if (st.empty()) {
          break;
        }
        k = getNextKid(st.back());
      }
      if (k) {
        st.push_back(k);
        pathSum += values[k];
      }
    }
    long long ret{0};
    function<void(int i, long long curr)> findMax = [&](int i, long long curr) {
      if (i > edges.size()) {
        return;
      }
      findMax(i + 1, curr);
      int allNoneZero = 1;
      for (const auto& [pathSum, pathSet] : pathToLeaf) {
        if (pathSet.count(i)) {
          allNoneZero = pathSum - values[i];
        }
      }
      if (allNoneZero) {
        ret = max(ret, curr);
      }
    };
    findMax(0, 0);
    return ret;
  }
};