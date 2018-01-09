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
Classic DP.

let dp[i][j] =
| T[0,j) is a subsequence of S[0, i) -> the largest index k such that S[k, i) has T[0, j) as subsequence.
| _                                  -> -1

Then
dp[i][j] =
match i with
| 0     -> when i == 0, S[0, 0) is empty, and only empty can be a subsequence of an empty string:
           dp[0][j] = j == 0? 0; -1;
| i < j -> -1, as T[0, j) is longer than S[k, i)
| _     -> match j with
          | 0 -> T[0, 0) is empty, and is a subsequence of any string, so dp[i][0] = i - 1 (recall we track largest)
          | 1 -> T[0, 1) has one character T[0], so we check
                 match T[0] with
                 | S[i - 1]  -> i - 1
                 | _         -> dp[i-1][j] because we just consider substring S[0, i-1) to find the largest index k
                                such that S[k] = T[0]
          | _ -> match T[j - 1] with
                 | S[i - 1] -> two possibilities to construct a solution: dp[i-1][j-1] or dp[i - 1][j], take the max
                 | _        -> only one way: dp[i - 1][j]

This dp recursive relation can be easily calculated by filling the whole table dp[0...n][0...m] 
where n = |S|, m = |T|, basically each cell depends on its immeidate above cell (dp[i-1][j]) 
and the left diag (dp[i-1][j-1]). So classic left to right downwards direction.

When filling the table, we keep looking at the solution of dp[i][m] for all i, as this 
is the index of S such that S[dp[i][m], i) contains T as a substring, and for each 
of these dp[i][m], we keep track of the minimal window (window length = i - dp[i][m]),
as well as the beginning index dp[i][m] of the window.

The solution is the minimal window and the beginning index dp[i][m] of the window.

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
