#include "cppCommonHeaders.hpp"

class Solution {
  using ull = unsigned long long;
  static constexpr ull kFNV64 = (1ull << 40) + (1ull << 8) + 0xb3;

 public:
  long long countPrefixSuffixPairs(vector<string>& words) {
    unordered_map<string, vector<int>> ends{};
    unordered_map<string, vector<ull>> h{};
    vector<ull> p{1};
    for (int i = 0; i < words.size(); ++i) {
      if (!h.count(words[i])) {
        auto [it, inserted] = h.emplace(words[i], vector<ull>(words[i].size()));
        for (ull prev = 0, j = 0; j < words[i].size();) {
          it->second[j] = prev = prev * kFNV64 + words[i][j] - 'a';
          if (++j == p.size()) {
            p.push_back(kFNV64 * p.back());
          }
        }
      }
      ends[words[i]].push_back(i);
    }
    ull ret = 0;
    for (auto it = ends.begin(); it != ends.end(); ++it) {
      ull cnt = it->second.size();
      ret += (cnt * (cnt - 1) / 2);
      it->second.push_back(words.size());
    }
    ends[words.back()].pop_back();
    ends[words.back()].back() = words.size();
    for (int i = words.size() - 2; i >= 0; --i) {
      for (int j = i + 1; j < ends[words[i]].back(); ++j) {
        const auto &lhs = h[words[i]], &rhs = h[words[j]];
        if (lhs.size() >= rhs.size()) {
          continue;
        }
        if (lhs.back() != rhs[lhs.size() - 1]) {
          continue;
        }
        if (lhs.back() !=
            rhs.back() - rhs[rhs.size() - lhs.size() - 1] * p[lhs.size()]) {
          continue;
        }
        ret += (ends[words[i]].size() - 1);
      }
      ends[words[i]].pop_back();
    }
    return ret;
  }
};

int main() {
  Solution sol{};
  vector<string> words{
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa",
      "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa", "aaaaa"};
  cout << sol.countPrefixSuffixPairs(words) << endl;
}