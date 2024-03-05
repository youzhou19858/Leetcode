#include "cppCommonHeaders.hpp"

class Solution {
 public:
  bool canWin(string str) {
    const int kN = str.size();
    // dp[i][j] => if there is a way to guarantee a win for str[i, j)
    vector<vector<char>> dp(kN + 1, vector<char>(kN + 1));
    for (int l = 2; l <= kN; ++l) {
      for (int inL = kN - l; inL >= 0; --inL) {
        for (int i = inL; i < inL + l - 1; ++i) {
          if (str[i] == '-' || str[i + 1] == '-') {
            continue;
          }
          if (dp[inL][inL + l] = !(dp[inL][i] ^ dp[i + 2][inL + l]);
              dp[inL][inL + l]) {
            cout << "dp(" << inL << ", " << inL + l << ") : " << inL << ", "
                 << i << " | " << i + 2 << ", " << inL + l << endl;
            break;
          }
        }
      }
    }
    for (const auto &vec : dp) {
      for (const auto ch : vec) {
        cout << (ch == 0 ? 0 : 1) << " ";
      }
      cout << endl;
    }
    return dp[0][kN];
  }
};

int main() {
  Solution sol;
  sol.canWin("+++++++++");
}