#include "cppCommonHeaders.hpp"

class Solution {
  using ull = unsigned long long;
  static constexpr ull kPrime = 1099511628211;
  string_view ret{};

 public:
  string longestDupSubstring(string_view s) {
    const string::size_type kN = s.size();
    vector<ull> h(kN + 1);
    vector<ull> p(kN + 1, 1);
    for (string::size_type i = 0; i < kN; ++i) {
      h[i + 1] = h[i] * this->kPrime + s[i];
      p[i + 1] = p[i] * this->kPrime;
    }
    function<string_view(string::size_type)> validate =
        [&](string::size_type len) {
          unordered_set<ull> seen{};
          for (auto i = len; i <= kN; ++i) {
            ull curHash = h[i] - h[i - len] * p[len];
            cout << "substr: " << s.substr(i - len, len) << " hash: " << curHash
                 << endl;
            const auto& [it, inserted] = seen.emplace(curHash);
            if (!inserted) {
              return s.substr(i - len, len);
            }
          }
          return string_view{};
        };
    int l = 0, r = kN - 1;
    while (l <= r) {
      cout << l << " " << r << endl;
      auto m = l + (r - l + 1) / 2;
      auto found = validate(m);
      if (found.empty()) {
        r = m - 1;
      } else {
        this->ret = found;
        l = m + 1;
      }
    }
    return {this->ret.begin(), this->ret.end()};
  }
};

int main() {
  Solution sol;
  cout << sol.longestDupSubstring("banana") << endl;
}