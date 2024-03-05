#include "cppCommonHeaders.hpp"

class Solution {
  template <char open, char close, typename Iter>
  vector<string> fn(Iter curr, const Iter kEnd) {
    vector<int> closedAt{};
    deque<char> checked{};
    int balance{0};
    for (; curr != kEnd; ++curr) {
      if (*curr == open) {
        --balance;
      } else if (*curr == close) {
        ++balance;
        closedAt.push_back(checked.size());
      }
      if constexpr (open == '(') {
        checked.push_back(*curr);
      } else {
        checked.push_front(*curr);
      }
      if (balance == 1) {
        if (closedAt.size() >= 2 &&
            *closedAt.rbegin() == *(closedAt.rbegin() + 1) + 1) {
          closedAt.pop_back();
        }
        auto others = fn<open, close>(++curr, kEnd);
        if (closedAt.empty()) {
          return others;
        } else {
          vector<string> ret{};
          for (int pos : closedAt) {
            string soFar(checked.begin(), checked.end());
            if constexpr (open == '(') {
              soFar.erase(soFar.begin() + pos);
              for (string& rhs : others) {
                ret.push_back(soFar + rhs);
              }
            } else {
              soFar.erase(soFar.end() - 1 - pos);
              for (string& lhs : others) {
                ret.push_back(lhs + soFar);
              }
            }
          }
          return ret;
        }
      }
    }
    if constexpr (open == '(') {
      if (balance < 0) {
        return fn<')', '('>(checked.rbegin(), checked.rend());
      }
    }
    if (checked.empty()) {
      return {""};
    }
    return {string(checked.begin(), checked.end())};
  }

 public:
  vector<string> removeInvalidParentheses(string s) {
    return fn<'(', ')'>(s.begin(), s.end());
  }
};

int main() {
  Solution sol{};
  vector<string> q{"()())()", "(a)())()", ")(", "x(", "(f", "(r(()()("};
  for (string& s : q) {
    auto ret = sol.removeInvalidParentheses(s);
    for (string& str : ret) {
    }
  }
}