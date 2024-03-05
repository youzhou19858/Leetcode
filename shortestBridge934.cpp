#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int shortestBridge(vector<vector<int>>& grid) {
    const int kN = grid.size();
    vector<pair<int, int>> outer{};
    for (int i = 0; i < kN; ++i) {
      for (int j = 0; j < kN; ++j) {
        if (grid[i][j]) {
          cout << "{" << i << ", " << j << "}" << endl;
          deque<pair<int, int>> dq{{i, j}};
          grid[i][j] = 2;
          while (dq.size()) {
            auto [r, c] = dq.front();
            cout << "{" << r << ", " << c << "}" << endl;
            dq.pop_front();
            int zeros = 0;
            if (r - 1 >= 0) {
              if (grid[r - 1][c] == 1) {
                grid[r - 1][c] = 2;
                dq.emplace_back(r - 1, c);
              } else if (grid[r - 1][c] == 0) {
                ++zeros;
              }
            }
            if (r + 1 < kN) {
              if (grid[r + 1][c] == 1) {
                grid[r + 1][c] = 2;
                dq.emplace_back(r + 1, c);
              } else if (grid[r + 1][c] == 0) {
                ++zeros;
              }
            }
            if (c - 1 >= 0) {
              if (grid[r][c - 1] == 1) {
                grid[r][c - 1] = 2;
                dq.emplace_back(r, c - 1);
              } else if (grid[r][c - 1] == 0) {
                ++zeros;
              }
            }
            if (c + 1 < kN) {
              if (grid[r][c + 1] == 1) {
                grid[r][c + 1] = 2;
                dq.emplace_back(r, c + 1);
              } else if (grid[r][c + 1] == 0) {
                ++zeros;
              }
            }
            if (zeros) {
              outer.emplace_back(r, c);
            }
          }
          break;
        }
      }
      if (outer.size()) {
        break;
      }
    }
    cout << outer.size() << endl;
    for (auto [i, j] : outer) {
      cout << "{" << i << ", " << j << "}" << endl;
    }
    for (int steps = 0; 1; ++steps) {
      vector<pair<int, int>> next{};
      for (auto [r, c] : outer) {
        if (r - 1 >= 0) {
          if (grid[r - 1][c] == 1) {
            return steps;
          } else if (grid[r - 1][c] == 0) {
            grid[r - 1][c] = 2;
            next.emplace_back(r - 1, c);
          }
        }
        if (r + 1 < kN) {
          if (grid[r + 1][c] == 1) {
            return steps;
          } else if (grid[r + 1][c] == 0) {
            grid[r + 1][c] = 2;
            next.emplace_back(r + 1, c);
          }
        }
        if (c - 1 >= 0) {
          if (grid[r][c - 1] == 1) {
            return steps;
          } else if (grid[r][c - 1] == 0) {
            grid[r][c - 1] = 2;
            next.emplace_back(r, c - 1);
          }
        }
        if (c + 1 < kN) {
          if (grid[r][c + 1] == 1) {
            return steps;
          } else if (grid[r][c + 1] == 0) {
            grid[r][c + 1] = 2;
            next.emplace_back(r, c + 1);
          }
        }
      }
      outer.swap(next);
    }
    return 0;
  }
};

int main() {
  vector<vector<int>> grid{{0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0},
                           {1, 1, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0}};
  Solution sol{};
  cout << sol.shortestBridge(grid) << endl;
}