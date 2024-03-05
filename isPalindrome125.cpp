#include "cppCommonHeaders.hpp"

class Solution {
 public:
  bool isPalindrome(string s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
      char lch = s[l];
      if (('a' > lch || lch > 'z') && ('A' > lch || lch > 'Z')) {
        ++l;
        continue;
      }
      char rch = s[r];
      if (('a' > rch || rch > 'z') && ('A' > rch || rch > 'Z')) {
        --r;
        continue;
      }
      cout << lch << " " << rch << endl;
      if (lch >= 'A' && lch <= 'Z') {
        lch = 'a' + (lch - 'A');
      }
      if (rch >= 'A' && rch <= 'Z') {
        rch = 'a' + (rch - 'A');
      }
      cout << lch << " " << rch << endl;
      if (lch != rch) {
        return false;
      }
      ++l;
      --r;
    }
    return true;
  }
};

int main() {
  Solution sol;
  sol.isPalindrome("A man, a plan, a canal: Panama");
  cout << tolower('0') << endl;
}