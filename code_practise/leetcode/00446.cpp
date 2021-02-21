/*
Condsider dp[i] = # of arithmetic slices ended in A[i].

This naive dp approach reveals that additional information is missing from the state definition.
Only with state info "end in i" does not yield a state transition function.

To extend the state, we need to refine the subproblem structure

Take 1:
consider dp[i][delta] = # of arithmetic slices ended in A[i] and the difference is delta.
then trivially, dp[i][delta] = \sum_{0<= j < i && A[i] - A[j] = delta} dp[j][delta] + # pairs (k, j) such that A[j] - A[k] = delta
and k < j < i.

The second clause poses a computational burden. This can be addressed by relaxing the subproblem def:
dp[i][delta] = # of arithmetic slices ended in A[i] and the difference is delta AND pairs of the form (j, i) where
A[i] - A[j] = delta.
then the recursion is simple: dp[i][delta] = \sum_{0<= j < i && A[i] - A[j] = delta} (dp[j][delta] + 1) 
note each j contribute 1 + dp[j][delta], as (i, j) is a valid form in the new def of subproblem.

this def of dp[i][delta] contains more than we need, but we know when looking at the subproblem dp[i][delta], all 
dp[j][delta] where 0 <= j < i && A[i] - A[j] = delta consititute to our final solution (just glue slice end at j
with difference delta onto A[i] as A[i] - A[j] = delta). In other words we just need to strip off the +1 from each j term.

How to compute? the # of delta can be huge (O(N^2)). Note, we don't need ALL dp[i][delta], 
we just need # of arithmetic slices ended in A[i] for EACH i. Thus we calculate for each i, only consider all 
the difference that COULD APPEAR BEFORE i:

for each i:
  for all j < i:
     delta = A[i] - A[j],
     some magic here
  done with all j < i, add i's contribution to final solution.   
  
And we expliot the fact that give i and delta, 
   dp[j][delta] 1. could have been calculated before as j < i
                2. none of the j < i can generate a delta, then THIS IS IMPOSSIBLE TO HAVE arithmetic slice end in j with delta
                   dp[j][delta] is naturally 0.
Therefore, the magic is to use dp[j][delta] directly:
dp[i][delta] += dp[j][delta] + 1;
The complete implementation:
*/

  using ll = long long;

    int numberOfArithmeticSlices(vector<int>& A) {
      if (A.size() < 3) {
        return 0;
      }
      vector<unordered_map<int, int>> dp(A.size());
      
      ll count = 0;
      for (int i = 1; i < A.size(); ++i) {
        for (int j = 0; j < i; ++j) {
          ll delta = ll(A[i]) - ll(A[j]);
          dp[i][delta] += dp[j][delta] + 1;
          count += dp[j][delta];
        }
      }
      return count;
    }
    
/*
Some points to note:
1. Note how to refine the subproblem to make computation fesible. We don't need to get final rst from dp table
directly, in fact, count is really a by-product from the computation:NONE of the entry in dp table is count.

2. The order of computation does not always align with the subproblem dependency graph. To calculate dp[i][delta],
it seems to depend on all entires dp[j][delta] to be calculated, for all j < i. In truth, dp[j][delta] is either
   2.1. calculated
   2.2. never been calculated. But the fact it is never calculated means none of the j < i can find a k < j such that
   A[j] - A[k] = delta. So it is impossible to have an arithmetic sequence end in j with delta, and the 
   contribution from j to i is 0 + 1 (you still have the pair (j, i) though). So never been calculated
   automatically means dp[j][delta]'s contribution is 0. This is a new techinique.

Despite the simplicity and novelty, this solution MLE due to too many hashtables.

Take 2:
recall we need to add state to dp[i] = # of arithmetic slices ended in A[i],
Condsider dp[i][j] = # of arithmetic slices ended in pair A[j] A[i], where j < i

Consider arithmetic seq ... A[k] ... A[j] A[i]. 
Then dp[i][j] = sum_{ 0 <= k < j && A[j] - A[k] = A[i] - A[j]} (dp[j][k] + 1)
The +1 comes from the fact that for all such k where 0 <= k < j && A[j] - A[k] = A[i] - A[j], 
the contirbution is either the arithmetic seq ... A[k] ... A[j] (in dp[j][k]), or A[k] A[j] (in +1)

Complete implementation.
*/
  using ll = long long;

    int numberOfArithmeticSlices(vector<int>& A) {
      if (A.size() < 3) {
        return 0;
      }
      vector<vector<int>> dp(A.size(), vector<int>(A.size(), 0)); 
      
      ll count = 0;
      for (int i = 2; i < A.size(); ++i) {
        for (int j = 1; j < i; ++j) {
          ll delta = ll(A[i]) - ll(A[j]);
          for (int k = 0; k < j; ++k) {
            if (ll(A[j]) - ll(A[k]) != delta) continue;
            dp[i][j] += dp[j][k] + 1;
          }
          count += dp[i][j];
        }
      }
      return count;
    }
    
/*
This trades off space complexity aganist time complextiy, and got accepted.
*/
