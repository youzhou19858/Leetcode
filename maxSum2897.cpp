#include "cppCommonHeaders.hpp"

class Solution {
  using ull = unsigned long long;
  static constexpr ull kMod = 10e9 + 7;

 public:
  int maxSum(vector<int>& nums, int k) {
    int zeros{0}, kN = (int)nums.size();
    while (kN - zeros > k) {
      printVec(nums);
      int ii{-1}, jj{kN}, minAnd{INT_MAX}, maxOr{INT_MIN};
      for (int i = 0; i < kN - 1; ++i) {
        if (!nums[i]) {
          continue;
        }
        for (int j = i + 1; j < kN; ++j) {
          if (!nums[j]) {
            continue;
          }
          int andVal{nums[i] & nums[j]}, orVal{nums[i] | nums[j]};
          if (orVal > maxOr || (orVal == maxOr && andVal < minAnd)) {
            ii = i;
            jj = j;
            maxOr = orVal;
            minAnd = andVal;
          }
        }
      }
      if (!minAnd) {
        ++zeros;
      }
      nums[ii] = minAnd;
      nums[jj] = maxOr;
    }
    ull ret{0};
    for (int num : nums) {
      ret = (ret + (num * num) % kMod) % kMod;
    }
    return (int)ret;
  }
};

int main() {
  Solution sol;
  vector<int> q{2, 6, 5, 8};
  cout << sol.maxSum(q, 2) << endl;
}