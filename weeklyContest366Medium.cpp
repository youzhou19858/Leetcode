#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int minOperations(string s1, string s2, int x) {
    const int kN = s1.size();
    int mismatches = 0;
    for (int i = 0; i < kN; ++i) {
      if (s1[i] != s2[i]) {
        ++mismatches;
      }
    }
    if (mismatches % 2 == 1) {
      return -1;
    }
    auto firstOp = [&s2, kN](const string &s) {
      vector<string> lkids{};
      vector<int> indices{};
      for (int i = 0; i < kN; ++i) {
        if (s[i] != s2[i]) {
          indices.push_back(i);
        }
      }
      const int kL = indices.size();
      for (int i = 0; i < kL - 1; ++i) {
        for (int j = i + 1; j < kL; ++j) {
          lkids.push_back(s);
          lkids.back()[indices[i]] =
              lkids.back()[indices[i]] == '0' ? '1' : '0';
          lkids.back()[indices[j]] =
              lkids.back()[indices[j]] == '0' ? '1' : '0';
        }
      }
      return lkids;
    };
    auto secondOp = [&s2, kN](const string &s) {
      vector<string> rkids{};
      for (int i = 0; i < kN - 1; ++i) {
        if (s[i] != s2[i] || s[i + 1] != s2[i + 1]) {
          rkids.push_back(s.substr(0, i) + (s[i] == '0' ? "1" : "0") +
                          (s[i + 1] == '0' ? "1" : "0") + s.substr(i + 2));
        }
      }
      return rkids;
    };
    unordered_map<string, int> seen{{s2, INT_MAX}};
    vector<pair<string, int>> curr{{s1, 0}};
    while (curr.size()) {
      vector<pair<string, int>> next{};
      for (const auto &[str, cost] : curr) {
        if (str == s2) {
          seen[str] = min(seen[str], cost);
          continue;
        }
        if (cost >= seen[s2]) {
          continue;
        }
        if (seen.count(str) && cost >= seen[str]) {
          continue;
        }
        seen[str] = cost;
        vector<string> lkids = firstOp(str);
        for (const auto &lkid : lkids) {
          next.emplace_back(lkid, cost + x);
        }
        vector<string> rkids = secondOp(str);
        for (const auto &rkid : rkids) {
          next.emplace_back(rkid, cost + 1);
        }
      }
      swap(curr, next);
    }
    return seen[s2] == INT_MAX ? -1 : seen[s2];
  }
};

int main() { Solution sol; }