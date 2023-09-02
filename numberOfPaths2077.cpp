#include "cppCommonHeaders.hpp"

class Solution {
 public:
  int numberOfPaths(int n, vector<vector<int>>& corridors) {
    vector<vector<int>> graph(n + 1, vector<int>());
    for (auto& e : corridors) {
      graph[e[0]].push_back(e[1]);
      graph[e[1]].push_back(e[0]);
    }
    vector<int> st{1}, visitedAtStep(n + 1);
    int ret{};
    while (st.size()) {
      int node = st.back(), cnt = (int)st.size();
      visitedAtStep[node] = cnt;
      for (auto kid : graph[node]) {
        if (visitedAtStep[kid]) {
          if ((cnt - visitedAtStep[kid]) == 2) {
            ++ret;
          } else if ((cnt + 1) < visitedAtStep[kid]) {
            st.push_back(kid);
            break;
          }
          continue;
        }
        st.push_back(kid);
        break;
      }
      if ((int)st.size() == cnt) {
        st.pop_back();
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  vector<vector<int>> q{{4, 1}, {4, 2}, {3, 4}, {5, 3}, {5, 2},
                        {1, 3}, {3, 2}, {2, 1}, {5, 4}, {5, 1}};
  cout << sol.numberOfPaths(5, q) << endl;
}