#include "cppCommonHeaders.hpp"

class Solution {
 public:
  vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
    const int kN = positions.size();
    vector<int> ret{};
    ret.reserve(kN);
    vector<vector<pair<int, int>>> parent(
        m, vector<pair<int, int>>(n, make_pair(-1, -1)));
    auto hash = [](const pair<int, int>& p) { return p.first * 31 + p.second; };
    function<pair<int, int>(int i, int j)> find = [&](int i, int j) {
      auto [a, b] = parent[i][j];
      if (a == i && b == j) {
        return parent[i][j];
      }
      return parent[i][j] = find(a, b);
    };
    unordered_set<pair<int, int>, decltype(hash)> roots{8, hash};
    for (const auto& vec : positions) {
      unordered_set<pair<int, int>, decltype(hash)> ps{4, hash};
      int a = vec[0], b = vec[1];
      if (a - 1 >= 0 && parent[a - 1][b].first != -1) {
        ps.insert(find(a - 1, b));
      }
      if (a + 1 < m && parent[a + 1][b].first != -1) {
        ps.insert(find(a + 1, b));
      }
      if (b - 1 >= 0 && parent[a][b - 1].first != -1) {
        ps.insert(find(a, b - 1));
      }
      if (b + 1 < n && parent[a][b + 1].first != -1) {
        ps.insert(find(a, b + 1));
      }
      if (ps.empty()) {
        roots.insert(parent[a][b] = make_pair(a, b));
      } else {
        roots.insert(parent[a][b] = *ps.begin());
        for (auto it = ++ps.begin(); it != ps.end(); ++it) {
          if (auto pos = roots.find(*it); pos != roots.end()) {
            roots.erase(*it);
          }
          parent[it->first][it->second] = parent[a][b];
        }
      }
      ret.push_back(roots.size());
    }
    return ret;
  }
};

int main() {
  Solution sol{};
  vector<vector<int>> q{{0, 0}, {0, 1}, {1, 2}, {2, 1}};
  auto ans = sol.numIslands2(3, 3, q);
  for (auto e : ans) {
      }
  }