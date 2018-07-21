#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

/*
find l such that [0...l) and [l... n)
maximize abs(max[0...l) - max[l...n))
*/

int solver(const vector<int> & vals) {
  int n = vals.size();
  const int INT_MIN = numeric_limits<int>::min();
  if (n < 2) return 0;
  // n >= 2;
  vector<int> maxsl(n, INT_MIN), maxsr(n, INT_MIN);
  for (int l = 1; l < n; ++l) {
    maxsl[l] = max(maxsl[l - 1], vals[l - 1]);
  }
  maxsr[n - 1] = vals.back();
  for (int l = n - 2; l >= 0; --l) {
    maxsr[l] = max(maxsr[l + 1], vals[l]);
  }

  int best = INT_MIN;
  for (int l = 1; l < n; ++l) {
    best = max(best, abs(maxsl[l] - maxsr[l]));
  }

  return best;
}

int main() {
  /*
  n/a 1 2 3
    4 4 4 4
  */
  cout << solver({100,2}) << endl;
  cout << solver({1,2,3}) << endl;
  cout << solver({1,2,3,4}) << endl;
  cout << solver({2,14,3,1}) << endl;
  cout << solver({3,2,3,100}) << endl;
}
