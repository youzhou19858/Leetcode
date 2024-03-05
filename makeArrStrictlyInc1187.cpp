#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
    if (arr1.size() < 2) {
      return 0;
    }
    sort(arr2.begin(), arr2.end());
    vector<int> currLevel(2, INT_MAX);
    currLevel[0] = arr1[0];
    if (arr2[0] < arr1[0]) {
      currLevel[1] = arr2[0];
    }
    for (int i = 1; i < arr1.size(); ++i) {
      printVec(currLevel);
      vector<int> nextLevel(i + 2, INT_MAX);
      for (int j = 0; j <= i; ++j) {
        if (currLevel[j] == INT_MAX) {
          continue;
        }
        if (currLevel[j] < arr1[i]) {
          nextLevel[j] = min(nextLevel[j], arr1[i]);
        }
        auto it = upper_bound(arr2.begin(), arr2.end(), currLevel[j]);
        if (it != arr2.end()) {
          nextLevel[j + 1] = min(nextLevel[j + 1], *it);
        }
      }
      swap(currLevel, nextLevel);
    }
    for (int i = 0; i <= arr1.size(); ++i) {
      if (currLevel[i] != INT_MAX) {
        return i;
      }
    }
    return -1;
  }
};

int main() {
  vector<int> arr1{1, 5, 3, 6, 7}, arr2{4, 3, 1};
  Solution sol;
  cout << sol.makeArrayIncreasing(arr1, arr2) << endl;
}