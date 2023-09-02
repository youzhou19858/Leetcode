#include "cppCommonHeaders.hpp"

class Solution {
 public:
  vector<int> findAllPeople(int n, vector<vector<int>>& meetings,
                            int firstPerson) {
    vector<int> sharedAt(n, INT_MAX);
    sharedAt[0] = sharedAt[firstPerson] = 0;
    auto comp = [&sharedAt](int pi, int pj) {
      return sharedAt[pi] < sharedAt[pj] ||
             (sharedAt[pi] == sharedAt[pj] && pi < pj);
    };
    vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
    for (auto& vec : meetings) {
      graph[vec[0]].emplace_back(vec[1], vec[2]);
      graph[vec[1]].emplace_back(vec[0], vec[2]);
    }
    set<int, decltype(comp)> sharedPeople(comp);
    sharedPeople.insert(0);
    sharedPeople.insert(firstPerson);
    unordered_set<int> ret{};
    while (sharedPeople.size()) {
      int earliest = *sharedPeople.begin();
      sharedPeople.erase(sharedPeople.begin());
      ret.insert(earliest);
      for (const auto& [p, t] : graph[earliest]) {
        if (!ret.count(p) && sharedAt[earliest] <= t && t < sharedAt[p]) {
          auto it = sharedPeople.find(p);
          if (it != sharedPeople.end()) {
            sharedPeople.erase(it);
          }
          sharedAt[p] = t;
          sharedPeople.insert(p);
        }
      }
    }
    return vector<int>(ret.begin(), ret.end());
  }
};