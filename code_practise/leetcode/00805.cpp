/*
 * Digestion:
 * Note that by elementry math we know if S1 is a subset satisfy the requirement,
 * then
 * ||S|| * n1 = ||S1|| * n
 * where n = |S| and ||S|| is the sum of set S
 *
 * This hints that we need to consider all subset that satisfy:
 * ||S1|| == ||S|| * n1 / n
 * and ||S|| * n1 / n == 0
 * Note the second condition does not involve S1, and can be enumerated
 * efficiently: n1 in [1, n)
 *
 * Therefore, all we need to do is to answer question of the form:
 *    Is it possible to have a subset S1 having a target sum j with size i?
 * efficiently. That is, we are to fill the table:
 *    dp[i][j] = true | false
 *
 * Note dp is sparse w.r.t the second component. This is common. This hints
 * we should do top-down with memorization/caching. To have a subopt structure,
 * we extend the state:
 *    dp[i][k][j] = Is it possible to have a subset S1 having a target sum j
 *                  with size i using only the first k elements?
 * Then the recursion is merely:
 *    dp[i][k][j] = dp[i][k-1][j] or there exists l in [i - 1, k) such that
 *                  dp[i - 1][l][j - num[l]] is true
 * Boundary condition: i >= 0, k >= 0, i <= k, k == 0
 */
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define DEBUG

#ifdef DEBUG
  #define OUTPUT(x) x;
#else
  #define OUTPUT(x)
#endif

class Solution {
  vector<int> num;
  int n;

   vector<vector<unordered_map<int, bool>>> dp;

   // return true if and only if there exists
   // i element in the first k element such that
   // their sum is sum
   bool calHelper(int i, int sum, int k) {
     if (k < 0 || i < 0) return false;
     if (i > k) return false;
     if (k == 0) return i == 0 && sum == 0;

     if (dp[i][k].count(sum) > 0) return dp[i][k][sum];

     bool &ans = dp[i][k][sum];
     // without num[k - 1]
     if (calHelper(i, sum, k - 1)) {
       return (ans = true);
     }

     // with num[k - 1]
     for (int l = i - 1; l < k; ++l) {
       if (calHelper(i - 1, sum - num[k - 1], l)) {
         return (ans = true);
       }
     }

     //cout << "false" << endl;
     return (ans = false);
   }

   bool cal(int i, int sum) {
     return calHelper(i, sum, n);
   }

public:
    bool splitArraySameAverage(vector<int> A) {
      n = A.size();
      swap(A, num);
      dp.resize(n + 1);
      for (auto & slice : dp) { slice.resize(n + 1); }

      int S = 0;
      for (auto e : num) { S += e; }

      for (int n1 = 1; n1 < n; ++n1) {
        if ((S * n1) % n == 0 && cal(n1, (S * n1) / n)) {
          return true;
        }
      }

      return false;
    }
};

int main() {
  Solution s;
  {
    bool ret = s.splitArraySameAverage(
      {1, 1}
    );
    DEBUG(cout << ret << endl);
    assert(ret);
  }
  {
    bool ret = s.splitArraySameAverage(
      { 1,2,3,4,5,6,7,8 }
    );
    DEBUG(cout << ret << endl);
    assert(ret);
  }
  DEBUG(
    cout << "...Passed" << endl
  );
}
