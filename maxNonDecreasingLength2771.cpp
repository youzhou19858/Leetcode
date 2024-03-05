#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int maxNonDecreasingLength1(vector<int>& nums1, vector<int>& nums2) {
    const int kN = nums1.size();
    vector<int> nums3{min(nums1[0], nums2[0])};
    nums3.reserve(kN);
    int inL = 0, exR = 1;
    for (int i = 1; i < kN; ++i) {
      auto [smaller, bigger] = minmax(nums1[i], nums2[i]);
      if (exR == i) {
        if (nums3[exR - 1] <= smaller) {
          nums3.push_back(smaller);
          ++exR;
        } else if (nums3[exR - 1] <= bigger) {
          nums3.push_back(bigger);
          ++exR;
        } else {
          nums3.push_back(smaller);
        }
      } else {
        if (nums3.back() <= smaller) {
          nums3.push_back(smaller);
        } else if (nums3.back() <= bigger) {
          nums3.push_back(bigger);
        } else {
          nums3.push_back(smaller);
        }
        int startAt = nums3.size() - 1;
        for (; startAt - 1 >= 0 && nums3[startAt - 1] <= nums3[startAt];
             --startAt)
          ;
        if (nums3.size() - startAt >= exR - inL) {
          inL = startAt;
          exR = nums3.size();
        }
      }
    }
    return exR - inL;
  }
  int maxNonDecreasingLength2(vector<int>& nums1, vector<int>& nums2) {
    const int kN = nums1.size();
    int ret = 1;
    function<void(const int, const int)> fn = [&](const int kInL,
                                                  const int kExR) {
      const int kLen = kExR - kInL;
      vector<int> nums3{min(nums1[kInL], nums2[kInL])};
      nums3.reserve(kLen);
      int inL = kInL, exR = kInL + 1;
      for (int i = kInL + 1; i < kExR; ++i) {
        auto [smaller, bigger] = minmax(nums1[i], nums2[i]);
        if (exR == i) {
          if (nums3[exR - kInL - 1] <= smaller) {
            nums3.push_back(smaller);
            ++exR;
          } else if (nums3[exR - kInL - 1] <= bigger) {
            fn(i, kExR);
            nums3.push_back(bigger);
            ++exR;
          } else {
            nums3.push_back(smaller);
          }
        } else {
          if (nums3.back() <= smaller) {
            nums3.push_back(smaller);
          } else if (nums3.back() <= bigger) {
            fn(i, kExR);
            nums3.push_back(bigger);
          } else {
            nums3.push_back(smaller);
          }
          int startAt = nums3.size() - 1;
          for (; startAt - 1 >= 0 && nums3[startAt - 1] <= nums3[startAt];
               --startAt)
            ;
          if (nums3.size() - startAt >= exR - inL) {
            inL = kInL + startAt;
            exR = kInL + nums3.size();
          }
        }
      }
      ret = max(ret, exR - inL);
    };
    fn(0, kN);
    return ret;
  }
  int maxNonDecreasingLength3(vector<int>& nums1, vector<int>& nums2) {
    const int kN = nums1.size();
    int ret = 1;
    vector<vector<int>> checked(kN + 1, vector<int>(kN + 1));
    function<void(const int, const int)> fn = [&](const int kInL,
                                                  const int kExR) {
      const int kLen = kExR - kInL;
      if (!kLen || checked[kInL][kExR]) {
        return;
      }
      vector<int> nums3{min(nums1[kInL], nums2[kInL])};
      nums3.reserve(kLen);
      int inL = kInL, exR = kInL + 1;
      for (int i = kInL + 1; i < kExR; ++i) {
        auto [smaller, bigger] = minmax(nums1[i], nums2[i]);
        if (exR == i) {
          if (nums3[exR - kInL - 1] <= smaller) {
            nums3.push_back(smaller);
            ++exR;
          } else if (nums3[exR - kInL - 1] <= bigger) {
            fn(i, kExR);
            nums3.push_back(bigger);
            ++exR;
          } else {
            nums3.push_back(smaller);
          }
        } else {
          if (nums3.back() <= smaller) {
            nums3.push_back(smaller);
          } else if (nums3.back() <= bigger) {
            fn(i, kExR);
            nums3.push_back(bigger);
          } else {
            nums3.push_back(smaller);
          }
          int startAt = nums3.size() - 1;
          for (; startAt - 1 >= 0 && nums3[startAt - 1] <= nums3[startAt];
               --startAt)
            ;
          if (nums3.size() - startAt >= exR - inL) {
            inL = kInL + startAt;
            exR = kInL + nums3.size();
          }
        }
      }
      checked[kInL][kExR] = max(checked[kInL][kExR], exR - inL);
      ret = max(ret, checked[kInL][kExR]);
    };
    fn(0, kN);
    return ret;
  }
};

int main() {
  vector<int> nums1{11, 7, 7, 9}, nums2{19, 19, 1, 7};
  Solution sol;
  cout << sol.maxNonDecreasingLength1(nums1, nums2) << endl;
}