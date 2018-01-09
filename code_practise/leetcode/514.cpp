class Solution {
  int MAX = numeric_limits<int>::max() - 1;
  unordered_map<char, unordered_set<int>> c; // char -> list of index in ring;
  vector<vector<int>> dp;
  int n, m;
  int rotatel(int i, int j) { // rotate i -> j
    return (j - i + m) % m;
  }
  
  int rotater(int i, int j) {
    return m - rotatel(i, j);
  }
  
  int helper(int i, int j, const string& ring, const string& key) {
    if (dp[i][j] != -1) {
      return dp[i][j];
    }
    
    if (i == 0) {
      return 0;
    }
    
    if (c[key[i - 1]].count(j) == 0) {
      return MAX;
    }
    
    if (i == 1) {
      return 1 + min(rotatel(0, j), rotater(0, j));
    }
    
    int cur = MAX;
    for (auto alpha : c[key[i - 2]]) {
       cur = min(cur, helper(i - 1, alpha, ring, key) + 1 + min(rotatel(j, alpha), rotater(j, alpha)));
    }
    dp[i][j] = cur;
    
    return cur;
  }
  
public:
    int findRotateSteps(string ring, string key) {
        m = ring.size();
        n = key.size();
        dp = vector<vector<int>>(n+1, vector<int>(m+1, -1));
        for (int i = 0; i < m; ++i) {
          c[ring[i]].insert(i);
        }
        
        int cur = MAX;
        for (auto alpha : c[key[n-1]]) {
          cur = min(cur, helper(n, alpha, ring, key));
        }
        return cur;
    }
};

/*
dp memorization

let n = |key|, m = |ring|
let state (i, j) = key[0, i) has been entered and the cursor stops at index j on ring.
let dp[i][j] = the minimal step to reach state(i, j)
solve min{dp(n, alpha), where ring[alpha] = key[n - 1]}

from state(i, j) to state(i + 1, k), where ring[j] = key[i-1], ring[k] = key[i],
one needs to do
rotatel(j, k) or rotater(j, k) (clock wise or counter clock wise)
and press the button.

thus the suboptimal structure:
dp[i][j] = match j with
           | ring[j] != key[i-1] -> INT_MAX (this step is useless, in fact, this cannot be reached, see match below)
           | _                   -> match i with
                                    | 0 -> 0 (nothing entered)
                                    | 1 -> 1 + min(rotater(0, k), rotatel(0, k)) where for all k such that ring[k] = key[0]
                                    | _ -> min(dp[i - 1][k] + 1 + min(rotater(j, k), rotatel(j, k)) 
                                           where for all k such that ring[k] = key[i - 2] (this ensures recursive call 
                                           will not pattern match the first arm of j)
                                           
Recusive implementation with a dp table for memorization.

"godding"
"gd"
"godding"
"g"
"godding"
"dd"
"godding"
"dod"
"godding"
"gniddog"
"godding"
"gni"
"godding"
"gniddog"

4
1
4
7
14
6
14
*/
