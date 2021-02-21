/*
> lc submit 546.remove-boxes.cpp
  ✔ Accepted
  ✔ 60/60 cases passed (171 ms)
  ✔ Your runtime beats 38.86 % of cpp submissions

> cat 546.test
[1, 3, 2, 2, 2, 3, 4, 3, 1]
[1,2,1,2]
[2]
[4, 6, 5, 8, 4, 8, 6, 9, 6, 2, 8, 6, 4, 1, 9, 5, 3]
[3, 8, 8, 5, 5, 3, 9, 2, 4, 4, 6, 5, 8, 4, 8, 6, 9, 6, 2, 8, 6, 4, 1, 9, 5, 3, 10, 5, 3, 3, 9, 8, 8, 6, 5, 3, 7, 4, 9, 6, 3, 9, 4, 3, 5, 10, 7, 6, 10, 7]

Digestion
Let <[i, j), k> represent the optimal payoff on interval [i, j) with k
continous boxes with the same color box[i] to the LEFT of interval [i,j),
where k boxes are not necessarily immedately before i.
0 <= i <= j <= n.

That is, to find the maximal payoff when eliminting interval [i, j) AND some
continous boxes region to the left of i of length k with same color box[i],
immagining everything between the k boxes and i is gone:
k = 3, i = 7, j = 9
X, X, X, Y, X, Y, Y, X, X, Y

We have two choices:
1. We remove k boxes with box[i], then consider the rest <[i + 1, j), 0>
2. We find a box m with same color box[i], i < m <= j, then solve <[i + 1, m), 0>, then
   combine the left k boxes with box[m] and the rest: <[m, j), k + 1>:
   <k boxes of color box[i]> ... box[i], box[i + 1] ... box[m - 1], box[m] ... box[j - 1]
                                            <[i + 1, m), 0>
Thus the sub optimal structure:
<[i, j), k> =
| 0                                                                      when j <= i
| <[i + 1, j), 0> + (k + 1)^2                                            If this value is larger
| \E m \in (i, j) and box[m] = box[i], <[i + 1, m), 0> + <[m, j), k + 1> If this value is larger

The original solution = <[0, n), 0>
*/

class Solution {
   static const int sizeLimit = 102;
   int dp[sizeLimit][sizeLimit][sizeLimit];

   int n = 0;
   vector<int> b;

   int helper(int i, int j, int k) {
      if (i == j) return 0;
      if (dp[i][j][k] >= 0) return dp[i][j][k];
      int& best = dp[i][j][k];
      best = helper(i + 1, j, 0) + (k + 1) * (k + 1);
      for (int m = i + 1; m < j; ++m) {
         if (b[m] == b[i]) {
            best = std::max(best, helper(i + 1, m, 0) + helper(m, j, k + 1));
         }
      }
      return best;
   }

public:
    int removeBoxes(vector<int>& boxes) {
        n = boxes.size();
        if (n == 0) {
           return 0;
        }

        std::swap(b, boxes);
        for (int i = 0; i <= n; ++i) {
           for (int j = 0; j <= n; ++j) {
              for (int k = 0; k <= n; ++k) {
                 dp[i][j][k] = -1;
              }
           }
        }
        return helper(0, n, 0);
    }
};
