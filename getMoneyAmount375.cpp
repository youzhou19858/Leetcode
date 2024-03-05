#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int getMoneyAmount(int n) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for (int i = 1; i < n + 1; ++i) {
      for (int l = 2, j = l - 1 + i; j < n + 1; j = l++ + i) {
        if (l == 2) {
          dp[i][j] = i;
        } else if (l == 3) {
          dp[i][j] = i + 1;
        } else if (l == 4) {
          dp[i][j] = 2 * i + 2;
        } else if (l == 5) {
          dp[i][j] = i + j;
        } else if (l == 6) {
          dp[i][j] = 2 * j - 4;
        }
      }
    }
    for (int l = 7; l < n + 1; ++l) {
      for (int i = 1, j = l - 1 + i; j < n + 1; j = i++ + l) {
        dp[i][j] = INT_MAX;
        for (int k = i; k < j; ++k) {
          dp[i][j] = min(dp[i][j], k + max(dp[i][k - 1], dp[k + 1][j]));
        }
      }
    }
    return dp[1][n];
  }
};

int main() {
  vector<int> qs{1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  Solution sol;
  for (int n : qs) {
    cout << "n: " << n << " ans: " << sol.getMoneyAmount(n) << endl;
  }
}