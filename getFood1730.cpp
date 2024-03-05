#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int getFood(const vector<vector<char>>& grid) {
    const int kM = grid.size(), kN = grid.front().size();
    vector<vector<int>> steps(kM, vector<int>(kN, INT_MAX));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>>
        pq{};
    for (int i = 0; i < kM; ++i) {
      for (int j = 0; j < kN; ++j) {
        if (grid[i][j] == '*') {
          pq.emplace(0, i, j);
          steps[i][j] = 0;
          break;
        }
      }
      if (pq.size()) {
        break;
      }
    }
    while (!pq.empty()) {
      const auto [cost, i, j] = pq.top();
      pq.pop();
      if (i - 1 >= 0 && grid[i - 1][j] != 'X') {
        if (grid[i - 1][j] == '#') {
          return cost + 1;
        }
        if (steps[i - 1][j] > cost + 1) {
          pq.emplace(cost + 1, i - 1, j);
          steps[i - 1][j] = cost + 1;
        }
      }
      if (i + 1 < kM && grid[i + 1][j] != 'X') {
        if (grid[i + 1][j] == '#') {
          return cost + 1;
        }
        if (steps[i + 1][j] > cost + 1) {
          pq.emplace(cost + 1, i + 1, j);
          steps[i + 1][j] = cost + 1;
        }
      }
      if (j - 1 >= 0 && grid[i][j - 1] != 'X') {
        if (grid[i][j - 1] == '#') {
          return cost + 1;
        }
        if (steps[i][j - 1] > cost + 1) {
          pq.emplace(cost + 1, i, j - 1);
          steps[i][j - 1] = cost + 1;
        }
      }
      if (j + 1 < kN && grid[i][j + 1] != 'X') {
        if (grid[i][j + 1] == '#') {
          return cost + 1;
        }
        if (steps[i][j + 1] > cost + 1) {
          pq.emplace(cost + 1, i, j + 1);
          steps[i][j + 1] = cost + 1;
        }
      }
    }
    return -1;
  }
};

int main() {
  vector<vector<char>> grid{{'X', 'X', 'X', 'X', 'X', 'X'},
                            {'X', '*', 'O', 'O', 'O', 'X'},
                            {'X', 'O', 'O', '#', 'O', 'X'},
                            {'X', 'X', 'X', 'X', 'X', 'X'}};
  Solution sol;
}