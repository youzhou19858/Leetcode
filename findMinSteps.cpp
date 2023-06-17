#include "cppCommonHeaders.hpp"

class Solution {
  int minCnt = INT_MAX;
  template <typename It>
  void dfs(string st, It beg, It end, unordered_map<char, int>& cards,
           int cnt = 0) {
    while (beg != end && cnt < this->minCnt) {
      if (st.size() < 2 || st.back() != *(st.rbegin() + 1)) {
        st.push_back(*beg++);
      } else {
        if (st.back() == *beg) {
          this->dfs(string(st.begin(), st.end() - 2), ++beg, end, cards, cnt);
          for (; beg != end && st.back() == *beg; ++beg)
            ;
          cout << "remove " << st.substr(st.size() - 2) << endl;
          st.erase(st.size() - 2);
        } else {
          if (cards[st.back()]) {
            --cards[st.back()];
            cout << "remove " << st.substr(st.size() - 2) << endl;
            this->dfs(string(st.begin(), st.end() - 2), beg, end, cards,
                      cnt + 1);
            ++cards[st.back()];
          }
          st.push_back(*beg++);
        }
      }
    }
    if (st.size() == 1) {
      this->minCnt = min(this->minCnt, cnt);
    } else {
      for (auto it = st.begin(); it != st.end(); ++it) {
        if (cards[*it] >= 2) {
          cards[*it] -= 2;
          string str = string(st.begin(), it) + string(it + 1, st.end());
          this->dfs("", str.begin(), str.end(), cards, cnt + 2);
          cards[*it] += 2;
        }
      }
    }
  }

 public:
  int findMinStep(string board, string hand) {
    board.push_back('$');
    unordered_map<char, int> cards{};
    for (char ch : hand) {
      ++cards[ch];
    }
    this->dfs("", board.begin(), board.end(), cards);
    return this->minCnt == INT_MAX ? -1 : this->minCnt;
  }
};

int main() {
  auto sol = Solution();
  sol.findMinStep("RRYGGYYRRYYGGYRR", "GGBBB");
}
