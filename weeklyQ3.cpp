#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int minimumOperationsToWriteY(vector<vector<int>>& grid) {
    int n = grid.size(), y = (n / 2 + 1) * 3 - 2, other = n * n - y;
    vector<int> yCnt(3);
    yCnt[grid[n / 2][n / 2]] = 1;
    grid[n / 2][n / 2] = -1;
    for (int i = n / 2, j = n / 2, dist = 1; dist < n / 2 + 1; ++dist) {
      ++yCnt[grid[i + dist][j]];
      grid[i + dist][j] = -1;
      ++yCnt[grid[i - dist][j - dist]];
      grid[i - dist][j - dist] = -1;
      ++yCnt[grid[i - dist][j + dist]];
      grid[i - dist][j + dist] = -1;
    }
    // cout << "y0: " << yCnt[0] << " y1: " << yCnt[1] << " y2: " << yCnt[2]
    //      << endl;
    vector<int> otherCnt(3);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] != -1) {
          ++otherCnt[grid[i][j]];
        }
      }
    }
    int ret{INT_MAX};
    for (int yi = 0; yi < 3; ++yi) {
      for (int oi = 0; oi < 3; ++oi) {
        if (yi == oi) {
          continue;
        }
        ret = min(ret, y - yCnt[yi] + other - otherCnt[oi]);
      }
    }
    return ret;
  }
};

int main() {
  vector<vector<int>> mat{{0, 1, 0, 1, 0},
                          {2, 1, 0, 1, 2},
                          {2, 2, 2, 0, 1},
                          {2, 2, 2, 2, 2},
                          {2, 1, 2, 2, 2}};
  Solution sol{};
  cout << sol.minimumOperationsToWriteY(mat) << endl;
}