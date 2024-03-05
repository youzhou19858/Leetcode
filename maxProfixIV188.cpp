#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int maxProfit(const int kT, vector<int>& prices) {
    const int kN = prices.size();
    vector<pair<int, int>> inRanges{};
    prices.push_back(INT_MIN);
    for (int beg = prices[0], prev = beg, i = 1; i <= kN; ++i) {
      if (prices[i] > prev) {
        prev = prices[i];
        continue;
      }
      if (beg != prev) {
        inRanges.emplace_back(beg, prev);
      }
      beg = prev = prices[i];
    }
    const int kTotal = accumulate(inRanges.begin(), inRanges.end(), 0,
                                  [](int sum, const pair<int, int>& p) {
                                    return sum += (p.second - p.first);
                                  });
    const int kM = inRanges.size();
    if (kM <= kT) {
      return kTotal;
    }
    vector<vector<int>> dp(kM, vector<int>(kT));
    }
};

int main() {
  vector<int> prices{3, 5, 3, 4, 1, 4, 5, 0, 7, 8, 5, 6, 9, 4, 1};
  Solution sol{};
  cout << sol.maxProfit(2, prices) << endl;
}