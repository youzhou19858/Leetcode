#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int getDiscountPairs(vector<int> prices, int x) {
    sort(prices.begin(), prices.end());
    int ret{0};
    for (auto it = prices.begin(); it != prices.end(); ++it) {
      auto beg = it + 1;
      for (int toFind = x - *it; beg != prices.end() && toFind <= prices.back();
           toFind += x) {
        if (toFind < *it) {
          continue;
        }
        if (auto pos = lower_bound(beg, prices.end(), toFind);
            pos != prices.end() && *pos == toFind) {
          ++ret;
          beg = pos + 1;
          cout << "<" << *it << ", " << *pos << ">" << endl;
        }
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  sol.getDiscountPairs({31, 25, 85, 29, 35}, 60);
}