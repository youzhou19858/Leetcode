#include "cppCommonHeaders.hpp"

class Solution {
 public:
  vector<int> resultArray(vector<int>& nums) {
    const int kN = nums.size();
    if (kN < 2) {
      return nums;
    }
    auto greaterCount = [&](multiset<int>& s, int val) {
      auto it = upper_bound(s.begin(), s.end(), val);
      return distance(it, s.end());
    };
    vector<int> arr0{nums[0]}, arr1{nums[1]};
    multiset<int> s0{nums[0]}, s1{nums[1]};
    for (int i = 2; i < kN; ++i) {
      int a = greaterCount(s0, nums[i]), b = greaterCount(s1, nums[i]);
      if (a > b) {
        arr0.push_back(nums[i]);
        s0.insert(nums[i]);
      } else if (a < b) {
        arr1.push_back(nums[i]);
        s1.insert(nums[i]);
      } else if (a == b) {
        if (arr0.size() <= arr1.size()) {
          arr0.push_back(nums[i]);
          s0.insert(nums[i]);
        } else {
          arr1.push_back(nums[i]);
          s1.insert(nums[i]);
        }
      }
    }
    for (int num : arr1) {
      arr0.push_back(num);
    }
    return arr0;
  }
};