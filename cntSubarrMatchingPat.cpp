#include "cppCommonHeaders.hpp"

class Solution {
  vector<int> kmpTable(const string& needle) {
    int n = needle.length();
    vector<int> lps(n, 0);
    int len = 0;
    int i = 1;

    while (i < n) {
      if (needle[i] == needle[len]) {
        len++;
        lps[i] = len;
        i++;
      } else {
        if (len != 0) {
          len = lps[len - 1];
        } else {
          lps[i] = 0;
          i++;
        }
      }
    }
    return lps;
  }

  // KMP search algorithm, modified to count occurrences
  int kmpSearch(const string& haystack, const string& needle) {
    int m = haystack.length();
    int n = needle.length();
    vector<int> lps = kmpTable(needle);

    int i = 0;
    int j = 0;
    int count = 0;  // Count occurrences
    while (i < m) {
      if (needle[j] == haystack[i]) {
        j++;
        i++;
      }
      if (j == n) {
        count++;  // Increment count for each match
        j = lps[j - 1];
      } else if (i < m && needle[j] != haystack[i]) {
        if (j != 0) {
          j = lps[j - 1];
        } else {
          i++;
        }
      }
    }
    return count;
  }

 public:
  int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
    const int kN = nums.size(), kM = pattern.size();
    string haystack(kN - 1, ' '), needle(kM, ' ');
    for (int i = 1; i < kN; ++i) {
      if (nums[i - 1] < nums[i]) {
        haystack[i - 1] = 'a';
      } else if (nums[i - 1] == nums[i]) {
        haystack[i - 1] = 'b';
      } else {
        haystack[i - 1] = 'c';
      }
    }
    for (int i = 0; i < kM; ++i) {
      if (pattern[i] == 1) {
        needle[i] = 'a';
      } else if (pattern[i] == 0) {
        needle[i] = 'b';
      } else {
        needle[i] = 'c';
      }
    }
    return kmpSearch(haystack, needle);
  }
};

int main() {
  vector<int> nums{1, 4, 4, 1, 3, 5, 5, 3}, pattern{1, 0, -1};
  Solution sol{};
  cout << sol.countMatchingSubarrays(nums, pattern) << endl;
}