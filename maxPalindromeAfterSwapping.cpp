#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int maxPalindromesAfterOperations(vector<string>& words) {
    int ret = 0;  // Count of immediate palindromes
    vector<int> cnt(
        26, 0);  // Count of characters for forming additional palindromes

    // Step 1: Identify self-palindromic words and increment count
    for (const string& word : words) {
      vector<int> wordCount(26, 0);
      for (char c : word) {
        wordCount[c - 'a']++;
      }

      int oddCount = 0;
      for (int count : wordCount) {
        if (count % 2 != 0) {
          oddCount++;
        }
      }

      // If the word can form a palindrome by itself, increment ret
      if (oddCount <= 1) {
        ret++;
      } else {
        // Else, add its characters to the global cnt for later use
        for (int i = 0; i < 26; ++i) {
          cnt[i] += wordCount[i];
        }
      }
    }

    // Step 2 & 3: Use remaining characters to form additional palindromes
    int pairs = 0, singles = 0;
    for (int count : cnt) {
      pairs += count / 2;
      singles += count % 2;
    }

    // For every two pairs, we can form one palindrome, and for every single
    // character, we can potentially form a new palindrome
    int additionalPalindromes =
        pairs / 2;  // Use pairs to form as many palindromes as possible

    // If there are more singles than required for odd-length palindromes,
    // adjust the count This step may not be strictly necessary based on the
    // interpretation of how singles are used
    if (singles > additionalPalindromes) {
      additionalPalindromes += singles - additionalPalindromes;
    }

    return ret + additionalPalindromes;
  }
};

int main() {
  Solution sol{};
  vector<string> words{"ad", "chahc", "ccd"};
  cout << sol.maxPalindromesAfterOperations(words) << endl;
}