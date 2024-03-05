#include "cppCommonHeaders.hpp"

class Solution {
  using ull = unsigned long long;

 public:
  int maximumLength(vector<int>& nums) {
    unordered_map<ull, int> frequency{};
    ull maxNum{0};
    for (int num : nums) {
      ++frequency[num];
      maxNum = max(maxNum, (ull)num);
    }
    double root = sqrt(maxNum);
    ull kBound = (ull)ceil(root);
    if ((ull)floor(root) == kBound) {
      ++kBound;
    }
    int ret = 1;
    if (auto it = frequency.find(1); it != frequency.end()) {
      ret = max(1, (it->second & 1) ? it->second : it->second - 1);
      frequency.erase(it);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    const int kN = nums.size();
    for (int i = nums[0] == 1 ? 1 : 0;
         i < kN && ((kN - i) * 2 - 1 > ret && nums[i] < kBound); ++i) {
      if (frequency[nums[i]] == 1) {
        continue;
      }
      auto it = frequency.find(nums[i] * nums[i]);
      for (int cnt = 1; it != frequency.end();
           it = frequency.find(it->first * it->first)) {
        ret = max(ret, ++cnt * 2 - 1);
        if (it->second == 1) {
          break;
        }
        it->second = 1;
        if (it->first >= kBound) {
          break;
        }
      }
    }
    return ret;
  }
};

int main() {
  vector vec{14, 14, 196, 196, 38416, 38416};
  Solution sol{};
  cout << sol.maximumLength(vec) << endl;
}