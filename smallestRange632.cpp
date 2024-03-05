#include "cppCommonHeaders.hpp"

class Solution {
 public:
  vector<int> smallestRange(vector<vector<int>>& nums) {
    const int kN = nums.size();
    vector<pair<int, int>> ordered{};
    for (int i = 0; i < kN; ++i) {
      for (int num : nums[i]) {
        ordered.emplace_back(num, i);
      }
    }
    sort(ordered.begin(), ordered.end());
    vector<int> cnt(kN);
    int l = ordered.front().first, r = ordered.back().first, k = 0;
    deque<pair<int, int>> window;
    for (const auto& [num, idx] : ordered) {
      window.emplace_back(num, idx);
      if (!cnt[idx]++ && ++k == kN) {
        while (cnt[window.front().second] - 1) {
          --cnt[window.front().second];
          window.pop_front();
        }
        int a = window.begin()->first, b = window.rbegin()->first;
        if (b - a < r - l) {
          l = a;
          r = b;
        }
        while (k == kN) {
          auto [head, group] = window.front();
          window.pop_front();
          if (!--cnt[group]) {
            --k;
          }
        }
      }
    }
    return {l, r};
  }
};