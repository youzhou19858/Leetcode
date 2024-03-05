#include "cppCommonHeaders.hpp"

class Solution {
  using ll = long long;

 public:
  long long beautifulSubstrings(string s, int k) {
    unordered_set<char> vs{'a', 'e', 'i', 'o', 'u'};
    const int kN = s.size();
    if (kN == 1) {
      return 0;
    }
    ll ret = 0;
    unordered_map<int, unordered_map<int, char>> hasComb{};
    hasComb[0][0] = 1;
    for (int vcnt = 0, ccnt = 0, i = 0; i < kN; ++i) {
      int isV = vs.count(s[i]);
      vcnt += isV;
      ccnt += (1 - isV);
      if (vcnt && ccnt) {
        int mincnt = min(vcnt, ccnt);
        for (int minusV = vcnt - mincnt, minusC = ccnt - mincnt;
             min(minusV, minusC) < mincnt; ++minusV, ++minusC) {
          if (hasComb[minusV][minusC] &&
              ((ll)((ll)(vcnt - minusV) * (ll)(ccnt - minusC)) % k) == 0) {
            ++ret;
          }
        }
      }
      hasComb[vcnt][ccnt] = 1;
    }
    return ret;
  }
};