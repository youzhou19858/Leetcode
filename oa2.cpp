#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int getMinCost(int n, vector<int> a, vector<int> b, int m) {
    set<pair<int, int>> s{};
    for (int i = 0; i < n; ++i) {
      s.emplace(a[i], b[i]);
    }
    int ret{0};
    while (m--) {
      auto [val, inc] = *s.begin();
      ret += val;
      s.erase(s.begin());
      s.emplace(val + inc, inc);
    }
    return ret;
  }
};

int main() {
  Solution sol;
  cout << sol.getMinCost(3, {2, 1, 1}, {1, 2, 3}, 4) << endl;
}