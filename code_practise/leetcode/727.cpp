class Solution {

public:
    string minWindow(string S, string T) {
      int n = S.size(), m = T.size();
      vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
      int soFar = INT_MAX, cur = INT_MAX;
      
      for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
          if (i == 0 || j > i) {
            dp[i][j] = (j == 0) ? 0 : -1;
          } else if (j == 0) {
            dp[i][j] = i - 1;
          } else if (j == 1) {
            if (S[i - 1] == T[0]) {
              dp[i][j] = i - 1;
            } else {
              dp[i][j] = dp[i-1][j];
            }
          } else { // assert(i >= j && j > 1);
            if (S[i - 1] == T[j - 1]) {
              dp[i][j] = dp[i - 1][j - 1];
            }
            dp[i][j] = std::max(dp[i][j], dp[i-1][j]);
          }
          
          //cout<<setw(4) << dp[i][j] << " ";
        }
        
        //cout << endl;
        
        int newStart = dp[i][m];
        int newSoFar = i - newStart;
        if (newStart == -1 || newSoFar > soFar) {
          continue;
        }
        
        if (newSoFar < soFar || (newSoFar == soFar && newStart < cur)) {
          soFar = newSoFar;
          cur = newStart;
        }
      }
      
      if (cur != INT_MAX) {
         return S.substr(cur, soFar);
      }
      return "";
    }
};

/*
  cout << s.minWindow("abcdebdde", "bde") << endl;
  cout << s.minWindow("a", "a") << endl;
  cout << s.minWindow("aa", "a") << endl;
  cout << s.minWindow("aa", "b") << endl;
  cout << s.minWindow("aa", "aaa") << endl;
  cout << s.minWindow("abcdebdde", "bddd") << endl;
  cout << s.minWindow("abcdabfd", "abd") << endl;
  cout << s.minWindow("abcdebdde", "d") << endl;
  cout << s.minWindow("abcdebdde", "e") << endl;
  cout << s.minWindow("abcdebdde", "a") << endl;
  cout << s.minWindow("abcdebdde", "b") << endl;
  cout << s.minWindow("abcdebdde", "c") << endl;
  
bcde
a
a


bcdebdd
abcd
d
e
a
b
c
*/
