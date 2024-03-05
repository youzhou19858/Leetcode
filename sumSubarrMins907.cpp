#include "cppCommonHeaders.hpp"

class Solution {
  using ll = long long;
  static constexpr ll kMod = 10e9 + 7;

 public:
  int sumSubarrayMins(vector<int>& arr) {
    const ll kN = arr.size();
    vector<ll> prevLte(kN, -1), nextLte(kN, kN);
    for (ll i = 1; i < kN; ++i) {
      ll j = i - 1;
      for (; j >= 0 && arr[j] > arr[i]; j = prevLte[j])
        ;
      prevLte[i] = j;
    }
    for (ll i = kN - 2; i >= 0; --i) {
      int j = i + 1;
      for (; j < kN && arr[j] > arr[i]; j = nextLte[j])
        ;
      nextLte[i] = j;
    }
    ll ret{0};
    for (ll i = 0; i < kN; ++i) {
      cout << "arr[" << i << "]: " << arr[i] << " prevLte: " << prevLte[i]
           << " nextLte: " << nextLte[i] << " add: " << i - prevLte[i] << " * "
           << nextLte[i] - i +
                  (nextLte[i] < kN ? (arr[i] == arr[nextLte[i]]) : 0)
           << " * " << arr[i] << endl;
      ret = (ret + (i - prevLte[i]) *
                       (nextLte[i] - i +
                        (nextLte[i] < kN ? (arr[i] == arr[nextLte[i]]) : 0)) *
                       (ll)arr[i]) %
            kMod;
    }
    return (int)ret;
  }
};