#include "cppCommonHeaders.hpp"

class Solution {
  struct Island {
    vector<pair<int, int>> points{};
    int l{INT_MAX}, r{INT_MIN}, u{INT_MAX}, d{INT_MIN}, w{0}, h{0};
    unsigned long long hash = 1099511628211;
    bool isAdjusted = false;
    Island& adjust() {
      if (!isAdjusted) {
        w = r - l + 1;
        h = d - u + 1;
        for (auto& [x, y] : points) {
          x -= u;
          y -= l;
        }
        sort(points.begin(), points.end());
        isAdjusted = true;
      }
      return *this;
    }
    bool operator==(const Island& other) const {
      if (points.size() != other.points.size() ||
          ((w != other.w || h != other.h) && (w != other.h || h != other.w))) {
        return false;
      }
      return hash == other.hash;
    }
  };

 public:
  int numDistinctIslands(vector<vector<int>>& grid) {
    const int kM = grid.size(), kN = grid[0].size();
    vector<int> parent(kM * kN, -1);
    function<int(int)> find = [&find, &parent](int i) {
      if (parent[i] == -1) {
        return i;
      }
      return parent[i] = find(parent[i]);
    };
    auto unite = [&find, &parent](int i, int j) {
      int pi = find(i), pj = find(j);
      if (pi != pj) {
        parent[pi] = pj;
      }
    };
    for (int i = 0; i < kM; ++i) {
      for (int j = 0; j < kN; ++j) {
        if (grid[i][j]) {
          if (i - 1 >= 0 && grid[i - 1][j]) {
            unite(i * kN + j, (i - 1) * kN + j);
          }
          if (j - 1 >= 0 && grid[i][j - 1]) {
            unite(i * kN + j, i * kN + j - 1);
          }
        } else {
          parent[i * kN + j] = -2;
        }
      }
    }
    unordered_map<int, Island> islands{};
    for (int i = 0; i < kM; ++i) {
      for (int j = 0; j < kN; ++j) {
        int idx = i * kN + j;
        if (parent[idx] == -2) {
          continue;
        }
        int mark = find(idx);
        islands[mark].points.emplace_back(i, j);
        islands[mark].l = min(islands[mark].l, j);
        islands[mark].r = max(islands[mark].r, j);
        islands[mark].u = min(islands[mark].u, i);
        islands[mark].d = max(islands[mark].d, i);
      }
    }
    auto IslandHash = [](const Island& island) { return island.hash; };
    unordered_set<Island, decltype(IslandHash)> distinctIslands{16, IslandHash};
    for (auto& [mark, island] : islands) {
      distinctIslands.insert(island.adjust());
    }
    // for (const auto& island : distinctIslands) {
    //       //        << " d: " << island.d << endl;
    //   for (const auto& [x, y] : island.points) {
    //         //   }
    //       // }
    return distinctIslands.size();
  }
};

int main() {
  vector<vector<int>> matrix{
      {1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 1, 1}, {0, 0, 0, 1, 1}};
  Solution sol{};
}