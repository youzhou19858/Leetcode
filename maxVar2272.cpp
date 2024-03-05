#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int largestVariance(string s) {
    const int kN = s.size();
    if (kN < 3) {
      return 0;
    }
    vector<vector<int>> ch2idxs(26);
    for (int i = 0; i < kN; ++i) {
      ch2idxs[s[i] - 'a'].push_back(i);
    }
    int ret{0};
    for (int i = 0; i < 25; ++i) {
      if (ch2idxs[i].empty()) {
        continue;
      }
      for (int j = i + 1; j < 26; ++j) {
        if (ch2idxs[j].empty()) {
          continue;
        }
        int maxSum1{0}, curMax1{0}, maxSum2{0}, curMax2{0},
            M = ch2idxs[i].size(), N = ch2idxs[j].size();
        for (int ii = 0, jj = 0; ii < M || jj < N;) {
          if (ii == M || (jj != N && ch2idxs[i][ii] > ch2idxs[j][jj])) {
            if (M >= N) {
              curMax1 = max(-1, curMax1 - 1);
              curMax2 = max(1, curMax2 + 1);
            } else {
              curMax1 = max(1, curMax1 + 1);
              curMax2 = max(-1, curMax2 - 1);
            }
            maxSum1 = max(maxSum1, curMax1);
            maxSum2 = max(maxSum2, curMax2);
            ++jj;
            continue;
          }
          if (jj == N || (ii != M && ch2idxs[i][ii] < ch2idxs[j][jj])) {
            if (M >= N) {
              curMax1 = max(1, curMax1 + 1);
              curMax2 = max(-1, curMax2 - 1);
            } else {
              curMax1 = max(-1, curMax1 - 1);
              curMax2 = max(1, curMax2 + 1);
            }
            maxSum1 = max(maxSum1, curMax1);
            maxSum2 = max(maxSum2, curMax2);
            ++ii;
            continue;
          }
        }
        ret = max(ret, max(maxSum1, maxSum2));
      }
    }
    return ret;
  }
};