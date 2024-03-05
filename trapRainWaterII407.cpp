#include "cppCommonHeaders.hpp"

class Solution {
  static constexpr auto pHash = [](const std::pair<int, int>& p) {
    return std::hash<int>{}(p.first) ^ std::hash<int>{}(p.second);
  };
  using pset = unordered_set<pair<int, int>, decltype(pHash)>;
  static constexpr array<pair<int, int>, 4> kDirs{
      make_pair(-1, 0),
      make_pair(1, 0),
      make_pair(0, -1),
      make_pair(0, 1),
  };

 public:
  int trapRainWater(vector<vector<int>>& h) {
    const int kM = h.size(), kN = h.front().size();
    if (kM < 3 || kN < 3) {
      return 0;
    }
    map<int, pset> h2ijs{};
    for (int i = 0; i < kM; ++i) {
      for (int j = 0; j < kN; ++j) {
        h2ijs[h[i][j]].emplace(i, j);
      }
    }
    const auto outOfBdry = [&](int i, int j) {
      return i == -1 || i == kM || j == -1 || j == kN;
    };
    const auto bdry = [&](int i, int j) {
      int ret{INT_MAX};
      for (auto [di, dj] : kDirs) {
        int r = i + di, c = j + dj;
        if (outOfBdry(r, c)) {
          return 0;
        }
        if (h[r][c] == h[i][j]) {
          continue;
        }
        ret = min(ret, h[r][c]);
      }
      return ret;
    };
    int ret{0};
    while (h2ijs.size()) {
      auto& [lv, s] = *h2ijs.begin();
      if (s.empty()) {
        h2ijs.erase(lv);
        continue;
      }
      vector<pair<int, int>> island{*s.begin()};
      int lowBdry = bdry(s.begin()->first, s.begin()->second);
      s.erase(s.begin());
      for (int k = 0; k < island.size(); ++k) {
        auto [i, j] = island[k];
        for (auto [di, dj] : kDirs) {
          int r = i + di, c = j + dj;
          if (outOfBdry(r, c) || h[r][c] != lv) {
            continue;
          }
          if (auto it = s.find({r, c}); it == s.end()) {
            continue;
          } else {
            s.erase(it);
            island.emplace_back(r, c);
            lowBdry = min(lowBdry, bdry(r, c));
          }
        }
      }
      ret += (island.size() * max(0, lowBdry - lv));
      for (auto [r, c] : island) {
        h[r][c] = lowBdry;
        if (lowBdry) {
          h2ijs[lowBdry].emplace(r, c);
        }
      }
    }
    return ret;
  }
};