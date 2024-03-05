#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int minDeletions(string s) {
    vector<int> freqs(26);
    int maxFreq{0};
    for (char ch : s) {
      maxFreq = max(maxFreq, ++freqs[ch - 'a']);
    }
    vector<int> vec(maxFreq + 1);
    for (int freq : freqs) {
      ++vec[freq];
    }
    int ret{0};
    for (int freq = 1; freq <= maxFreq; ++freq) {
      int preFreq = freq - 1;
      while (vec[freq] > 1) {
        while (preFreq && vec[preFreq]) {
          --preFreq;
        }
        if (preFreq) {
          ret += (freq - preFreq);
          vec[preFreq] = 1;
        } else {
          ret += freq;
        }
        --vec[freq];
      }
    }
    return ret;
  }
};