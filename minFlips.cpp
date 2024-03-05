#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int minFlips(string target) {
    char curr = '1';
    int count = 0;
    for (int i = 0; i < target.length(); i++) {
      // If curr occurs in the final string
      if (target[i] == curr) {
        count++;

        // Switch curr to '0' if '1'
        // or vice-versa
        curr = (char)(48 + (curr + 1) % 2);
      }
    }
    return count;
  }
};

int main() {
  Solution sol;
  cout << sol.minFlips("01011") << endl;
}