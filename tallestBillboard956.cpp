#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int tallestBillboard(vector<int>& rods) {
    unordered_map<int, int> freqs{};
    int total{0};
    for (int num : rods) {
      total += num;
      ++freqs[num];
    }
    vector<pair<int, int>> num2cnt(freqs.begin(), freqs.end());
    auto solve = [&](int k) {
      vector<vector<vector<vector<int>>>> dp(
          num2cnt.size(), vector<vector<vector<int>>>(k + 1));
      vector<vector<char>> checked(num2cnt.size(),
                                   vector<char>(num2cnt.size()));
      for (int cnt = 0; cnt <= num2cnt[0].second; ++cnt) {
        int val = num2cnt[0].first * cnt;
        if (val > k) {
          break;
        }
        dp[0][val].push_back({cnt});
      }
      for (int i = 1; i < num2cnt.size(); ++i) {
        for (int cnt = 0; cnt <= num2cnt[i].second; ++cnt) {
          int val = num2cnt[i].first * cnt;
          if (val > k) {
            break;
          }
          for (int j = val; j <= k; ++j) {
            for (vector<int> vec : dp[i - 1][j - val]) {
              vec.push_back(cnt);
              dp[i][j].push_back(vec);
            }
          }
        }
        const auto& validCombs = dp[i][k];
        for (int ii = 0; ii < validCombs.size() - 1; ++ii) {
          for (int jj = ii + 1; jj < validCombs.size(); ++jj) {
            if (checked[ii][jj]) {
              continue;
            }
            bool valid = true;
            for (int kk = 0; kk <= i; ++kk) {
              if (validCombs[ii][kk] + validCombs[jj][kk] >
                  num2cnt[kk].second) {
                valid = false;
                break;
              }
            }
            if (valid) {
              return true;
            }
            checked[ii][jj] = 1;
          }
        }
      }
      return false;
    };
    for (total /= 2; total; --total) {
      if (solve(total)) {
        return total;
      }
    }
    return 0;
  }
};

int main() {
  vector<int> q1{1, 2, 3, 6}, q2{1, 2, 3, 4, 5, 6}, q3{1, 2};
  Solution sol{};
  // cout << sol.tallestBillboard(q1) << endl;
  cout << sol.tallestBillboard(q2) << endl;
  // cout << sol.tallestBillboard(q3) << endl;
}