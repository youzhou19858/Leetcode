#include "cppCommonHeaders.hpp"

class Solution {
  using ull = unsigned long long;
  static constexpr ull kMod = 1e9 + 7;

 public:
  int numSubseq(vector<int>& nums, const int kT) {
    sort(nums.begin(), nums.end());
    deque<int> dq(nums.begin(), nums.end());
    vector<vector<ull>> combs{{1}, {1, 1}, {1, 2, 1}};
    auto allCombs = [&combs](const vector<vector<ull>>::size_type kN) {
      for (auto sz = combs.size(); sz <= kN; sz = combs.size()) {
        combs.push_back(vector<ull>(sz + 1, 1));
        for (vector<vector<ull>>::size_type r = 1; r < (sz + 1) / 2; ++r) {
          combs[sz][r] = combs[sz][sz - r] =
              combs[sz - 1][r] + combs[sz - 1][r - 1];
        }
        if ((sz + 1) & 1) {
          combs[sz][(sz + 1) / 2] =
              combs[sz - 1][(sz + 1) / 2] + combs[sz - 1][((sz + 1) / 2) - 1];
        }
      }
      ull cnt{0};
      const auto& vec = combs[kN];
      for (vector<vector<ull>>::size_type i = 0; i < (kN + 1) / 2; ++i) {
        cnt = (cnt + ((vec[i] << 1) % kMod)) % kMod;
      }
      if ((kN + 1) & 1) {
        cnt = (cnt + vec[kN / 2]) % kMod;
      }
      cout << "kN: " << kN << " cnt: " << cnt << endl;
      return cnt;
    };
    ull ret{0};
    while (dq.size()) {
      if (dq.front() + dq.back() <= kT) {
        ret = (ret + allCombs(dq.size() - 1)) % kMod;
        dq.pop_front();
      } else {
        dq.pop_back();
      }
    }
    for (auto& vec : combs) {
      printVec(vec);
    }
    return ret;
  }
};

int main() {
  Solution sol;
  vector<int> q{9,  25, 9,  28, 24, 12, 17, 8,  28, 7, 21, 25, 10, 2,
                16, 19, 12, 13, 15, 28, 14, 12, 24, 9, 6,  7,  2,  15,
                19, 13, 30, 30, 23, 19, 11, 3,  17, 2, 14, 20, 22, 30,
                12, 1,  11, 2,  2,  20, 20, 27, 15, 9, 10, 4,  12, 30,
                13, 5,  2,  11, 29, 5,  3,  13, 22, 5, 16, 19, 7,  19,
                11, 16, 11, 25, 29, 21, 29, 3,  2,  9, 20, 15, 9};
  cout << sol.numSubseq(q, 32) << endl;
}