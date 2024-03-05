#include "cppCommonHeaders.hpp"

class Solution {
 public:
  string minWindow(const string s, const string t) {
    const int kN = t.size(), kM = s.size();
    vector<unordered_map<int, int>> dp(kN, unordered_map<int, int>());
    vector<vector<int>> positions(26, vector<int>());
    for (int i = 0; i < kM; ++i) {
      if (s[i] == t.back()) {
        dp[kN - 1][i] = i;
      }
      positions[s[i] - 'a'].push_back(i);
    }
    for (int i = kN - 1; i; --i) {
      const vector<int>& idxs = positions[t[i - 1] - 'a'];
      for (const auto& [fixedAt, endsAt] : dp[i]) {
        if (auto it = lower_bound(idxs.begin(), idxs.end(), fixedAt);
            it != idxs.begin()) {
          if (dp[i - 1].count(*(it - 1))) {
            dp[i - 1][*(it - 1)] = min(dp[i - 1][*(it - 1)], endsAt);
          } else {
            dp[i - 1][*(it - 1)] = endsAt;
          }
        }
      }
    }
    int l = -1, r = kM;
    for (const auto& [fixedAt, endsAt] : dp[0]) {
      if (endsAt - fixedAt < r - l ||
          (endsAt - fixedAt == r - l && fixedAt < l)) {
        l = fixedAt;
        r = endsAt;
      }
    }
    return l < 0 ? "" : s.substr(l, r - l + 1);
  }
};