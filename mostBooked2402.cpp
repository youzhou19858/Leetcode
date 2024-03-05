#include "cppCommonHeaders.hpp"

class Solution {
  using ull = unsigned long long;

 public:
  int mostBooked(int n, vector<vector<int>>& meetings) {
    set<pair<ull, int>> availableRooms{};
    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
      availableRooms.emplace(0, i);
    }
    sort(meetings.begin(), meetings.end());
    auto comp = [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
      return lhs.second < rhs.second;
    };
    for (const auto& interval : meetings) {
      ull beg = interval[0], end = interval[1];
      auto stop = availableRooms.upper_bound(make_pair(beg, n));
      set<pair<ull, int>>::iterator it = availableRooms.begin();
      if (availableRooms.begin() != stop) {
        it = min_element(availableRooms.begin(), stop, comp);
      }
      auto [canBegin, room] = *it;
      availableRooms.erase(it);
      availableRooms.emplace(max(beg, canBegin) + end - beg, room);
      ++cnt[room];
    }
    return max_element(cnt.begin(), cnt.end()) - cnt.begin();
  }
};