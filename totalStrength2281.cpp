#include "cppCommonHeaders.hpp"

class Solution {
  using ll = long long;
  static constexpr ll kMod = 1e9 + 7;

 public:
  int totalStrength(vector<int>& strength) {
    const ll kN = strength.size();
    vector<ll> prevLte(kN, -1), nextLess(kN, kN),
        psum(strength.begin(), strength.end());
    for (ll i = 1, k = kN - 2; i < kN; ++i, --k) {
      psum[i] = (psum[i] + psum[i - 1]) % kMod;
      ll j = i - 1;
      for (; j >= 0 && strength[j] > strength[i]; j = prevLte[j])
        ;
      prevLte[i] = j;
      j = k + 1;
      for (; j < kN && strength[j] >= strength[k]; j = nextLess[j])
        ;
      nextLess[k] = j;
    }
    vector<ll> ppsum(psum.begin(), psum.end());
    for (int i = 1, j = kN - 2; i < kN; ++i, --j) {
      ppsum[i] = (ppsum[i] + ppsum[i - 1]) % kMod;
    }
    ll ret{0};
    for (ll i = 0; i < kN; ++i) {
      ll l = prevLte[i], r = nextLess[i], total = strength[i];
      if (r - l > 2) {
        total =
            ((((i - l) * (ppsum[r - 1] - (i < 1 ? 0 : ppsum[i - 1]))) % kMod) -
             (((r - i) *
               (i < 1 ? 0 : (ppsum[i - 1] - (l < 1 ? 0 : ppsum[l - 1])))) %
              kMod)) %
            kMod;
      }
      ret = (ret + (total * (ll)strength[i]) % kMod) % kMod;
    }
    return (ret + kMod) % kMod;
  }
};

int main() {
  Solution sol{};
  vector<int> vec{13, 13, 12, 12, 13, 12};
  cout << sol.totalStrength(vec) << endl;
}