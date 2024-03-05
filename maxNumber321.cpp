#include "cppCommonHeaders.hpp"

class Solution {
 public:
  vector<int> maxNumber(vector<int>& a, vector<int>& b, int k) {
    vector<int> ret{};
    ret.reserve(k);
    for (int dummy = -1; k; --k) {
      const int kLen = (int)(a.size() + b.size()) - k + 1;
      int* aPtr = a.empty()
                      ? &dummy
                      : max_element(&a[0], &a[0] + min((int)a.size(), kLen));
      int* bPtr = b.empty()
                      ? &dummy
                      : max_element(&b[0], &b[0] + min((int)b.size(), kLen));
      if (*aPtr < *bPtr) {
        ret.push_back(*bPtr);
        b.erase(b.begin(), b.begin() + (bPtr - &b[0] + 1));
      } else if (*aPtr > *bPtr) {
        ret.push_back(*aPtr);
        a.erase(a.begin(), a.begin() + (aPtr - &a[0] + 1));
      } else {
      }
    }
    return ret;
  }
};

int main() {
  vector<int> a{3, 9}, b{8, 9};
  Solution sol{};
  sol.maxNumber(a, b, 3);
}