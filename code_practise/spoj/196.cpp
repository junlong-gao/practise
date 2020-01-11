// https://www.spoj.com/problems/MUSKET/
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> dp;
vector<vector<bool>> a;
int n;

int f(int i, int j) {
   if (dp[i][j] != -1) {
      return dp[i][j];
   }
   int &ret = dp[i][j];
   if (i == j - 1) return ret = 1;
   for (int k = i + 1; k < j; ++k) {
      if (f(i, k) && f(k, j) && 
            (a[i%n][k%n] || a[j%n][k%n])) {
         return ret = 1;
      }
   }
   return ret = 0;
}

void solve(vector<int>& out) {
   cin >> n;

   a = vector<vector<bool>>(n, vector<bool>(n, false));
   for (int i = 0; i < n; ++i) {
      string s; cin >> s;
      for (int j = 0; j < n; ++j) {
         a[i][j] = (s[j] == '1');
      }
   }

   dp = vector<vector<int>>(2 * n, vector<int>(2 * n, -1));
   for (int i = 0; i < n; ++i) {
      if (f(i, i + n)) {
         out.push_back(i + 1);
      }
   }
}

int main() {
   int t; cin >> t;
   while (t-->0) {
      vector<int> out;
      solve(out);
      cout << out.size() << endl;
      for (auto e : out) {
         cout << e << endl;
      }
   }
   return 0;
}
