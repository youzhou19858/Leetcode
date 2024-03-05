#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "cmath"

using namespace std;

template <typename T>
void printVec(vector<T>& vec) {
  for (const auto& e : vec) {
    cout << e << ", ";
  }
  cout << endl;
}