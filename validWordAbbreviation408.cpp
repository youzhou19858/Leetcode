#include "cppCommonHeaders.hpp"
class Solution {
 public:
  bool validWordAbbreviation(string word, string abbr) {
    vector<string> tokens{};
    vector<int> nums{};
    string token{};
    int num{0};
    for (char ch : abbr) {
      if ('0' <= ch && ch <= '9') {
        if (token.size()) {
          tokens.push_back(token);
          token = "";
        }
        if (!(num = num * 10 + (ch - '0'))) {
          return false;
        }
      } else {
        if (num) {
          nums.push_back(num);
          num = 0;
        }
        token.push_back(ch);
      }
    }
    if (token.size()) {
      tokens.push_back(token);
    }
    if (num) {
      nums.push_back(num);
    }
    printVec(tokens);
    printVec(nums);
    const int kN = word.size();
    if (tokens.empty()) {
      return nums[0] == kN;
    }
    if (nums.empty()) {
      return tokens[0] == word;
    }

    return true;
  }
};

int main() {
  Solution sol;
  sol.validWordAbbreviation("substitution", "s10n");
  sol.validWordAbbreviation("substitution", "sub4u4");
  sol.validWordAbbreviation("substitution", "12");
  sol.validWordAbbreviation("substitution", "su3i1u2on");
  sol.validWordAbbreviation("substitution", "substitution");
  sol.validWordAbbreviation("internationalization", "i12iz4n");
}