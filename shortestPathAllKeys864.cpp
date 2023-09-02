#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int shortestPathAllKeys(vector<string>& grid) {
    const int kM = grid.size(), kN = grid.front().size();
    vector<tuple<int, int, int>> currNodes{};
    vector<vector<vector<int>>> visited(
        1 << 7, vector<vector<int>>(kM, vector<int>(kN)));
    int allKeys{};
    for (int i = 0; i < kM; ++i) {
      for (int j = 0; j < kN; ++j) {
        if (grid[i][j] == '@') {
          currNodes.emplace_back(0, i, j);
          visited[0][i][j] = 1;
        } else if (islower(grid[i][j])) {
          allKeys |= (1 << (grid[i][j] - 'a'));
        }
      }
    }
    vector<vector<vector<pair<int, int>>>> paths(
        kM, vector<vector<pair<int, int>>>(kN, vector<pair<int, int>>()));

    const vector<pair<int, int>> kMoves{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int steps = 1; currNodes.size(); ++steps) {
      vector<tuple<int, int, int>> nextNodes{};
      for (; currNodes.size(); currNodes.pop_back()) {
        auto [keys, i, j] = currNodes.back();
        for (auto [di, dj] : kMoves) {
          int newI = i + di, newJ = j + dj;
          if (newI < 0 || newI == kM || newJ < 0 || newJ == kN ||
              grid[newI][newJ] == '#') {
            continue;
          }
          if (isupper(grid[newI][newJ]) &&
              ((keys & (1 << (grid[newI][newJ] - 'A'))) == 0)) {
            continue;
          }
          if (islower(grid[newI][newJ])) {
            keys |= (1 << (grid[newI][newJ] - 'a'));
          }
          if (keys == allKeys) {
            return steps;
          }
          if (visited[keys][newI][newJ]) {
            continue;
          }
          visited[keys][newI][newJ] = 1;
          nextNodes.emplace_back(keys, newI, newJ);
          paths[i][j].emplace_back(newI, newJ);
        }
      }
      swap(currNodes, nextNodes);
    }
    return -1;
  }
};

int main() {
  Solution sol{};
  vector<string> q{".#.b.", "A.#aB", "#d...", "@.cC.", "D...#"};
  sol.shortestPathAllKeys(q);
}