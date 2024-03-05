#include "cppCommonHeaders.hpp"

class Solution {
  using ll = long long;

 public:
  long long subArrayRanges(vector<int>& nums) {
    const int kN = nums.size();
    vector<int> prevLess(kN), prevGreater(kN), nextLess(kN), nextGreater(kN);
    ll ret{0};
    int minAt = 0, maxAt = 0;
    prevLess[0] = prevGreater[0] = -1;
    for (int i = 1; i < kN; ++i) {
      if (nums[i] < nums[minAt]) {
        minAt = i;
      }
      if (nums[i] > nums[maxAt]) {
        maxAt = i;
      }
      int j = i - 1;
      for (; j >= 0 && nums[j] >= nums[i]; j = prevLess[j])
        ;
      prevLess[i] = j;
      j = i - 1;
      for (; j >= 0 && nums[j] <= nums[i]; j = prevGreater[j])
        ;
      prevGreater[i] = j;
    }
    nextLess[kN - 1] = nextGreater[kN - 1] = kN;
    for (int i = kN - 2; i >= 0; --i) {
      int j = i + 1;
      for (; j < kN && nums[j] >= nums[i]; j = nextLess[j])
        ;
      nextLess[i] = j;
      j = i + 1;
      for (; j < kN && nums[j] <= nums[i]; j = nextGreater[j])
        ;
      nextGreater[i] = j;
    }
    auto maxLessBefore = [&](int r, int i) {
      for (--r; r >= 0 && prevGreater[r] >= i; r = prevGreater[r])
        ;
      return r;
    };
    auto minGreaterAfter = [&](int l, int j) {
      for (++l; l < kN && nextLess[l] <= j; l = nextLess[l])
        ;
      return l;
    };
    auto minGreaterBefore = [&](int r, int i) {
      for (--r; r >= 0 && prevLess[r] >= i; r = prevLess[r])
        ;
      return r;
    };
    auto maxLessAfter = [&](int l, int j) {
      for (++l; l < kN && nextGreater[l] <= j; l = nextGreater[l])
        ;
      return l;
    };
    vector<vector<int>> added(kN, vector<int>(kN));
    function<void(int, int, int, int)> solve = [&](int i, int j, int minIdx,
                                                   int maxIdx) {
      if (i >= j || added[i][j]) {
        return;
      }
      auto [l, r] = minmax(minIdx, maxIdx);
      ret += (ll)((l - i + 1) * (j - r + 1)) *
             ((ll)nums[maxIdx] - (ll)nums[minIdx]);
      added[i][j] = 1;
      if (l == minIdx) {
        solve(i, r - 1, l, maxLessBefore(r, i));
        solve(l + 1, j, minGreaterAfter(l, j), r);
      } else {  // l == maxIdx && r == minIdx
        solve(i, r - 1, minGreaterBefore(r, i), l);
        solve(l + 1, j, r, maxLessAfter(l, j));
      }
    };
    solve(0, kN - 1, minAt, maxAt);
    return ret;
  }
};

int main() {
  vector<int> nums{22, -12, 88, 56, -3, -96};
  Solution sol{};
  cout << sol.subArrayRanges(nums) << endl;
}