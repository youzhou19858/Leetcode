#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int minOperations(vector<int>& nums) {
    const int kN = nums.size();
    set<int> setOfNums(nums.begin(), nums.end());
    int ret{0};
    for (int cntDiff = kN - setOfNums.size(),
             valDiff = *setOfNums.rbegin() - *setOfNums.begin();
         cntDiff || valDiff != kN - 1; cntDiff = kN - setOfNums.size(),
             valDiff = *setOfNums.rbegin() - *setOfNums.begin()) {
      ret += cntDiff;
      for (int num = *setOfNums.begin() + 1; cntDiff; ++num) {
        if (setOfNums.count(num)) {
          continue;
        }
        setOfNums.insert(num);
        --cntDiff;
      }
      auto it = setOfNums.lower_bound(*setOfNums.begin() + kN - 1);
      if (it == setOfNums.end() || *it != *setOfNums.begin() + kN - 1) {
        setOfNums.erase(--setOfNums.end());
        ++ret;
        setOfNums.insert(*setOfNums.begin() + kN - 1);
      } else {
        setOfNums.erase(it, setOfNums.end());
      }
    }
    return ret;
  }
};