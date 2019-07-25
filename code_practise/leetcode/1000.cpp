/*
 * @lc app=leetcode id=1000 lang=cpp
 *
 * [1000] Minimum Cost to Merge Stones
 *
 * https://leetcode.com/problems/minimum-cost-to-merge-stones/description/
 *
 * algorithms
 * Hard (33.12%)
 * Total Accepted:    4.3K
 * Total Submissions: 12.9K
 * Testcase Example:  '[3,2,4,1]\n2'
 *
 * There are N piles of stones arranged in a row.  The i-th pile has stones[i]
 * stones.
 * 
 * A move consists of merging exactly K consecutive piles into one pile, and
 * the cost of this move is equal to the total number of stones in these K
 * piles.
 * 
 * Find the minimum cost to merge all piles of stones into one pile.  If it is
 * impossible, return -1.
 * 
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: stones = [3,2,4,1], K = 2
 * Output: 20
 * Explanation: 
 * We start with [3, 2, 4, 1].
 * We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
 * We merge [4, 1] for a cost of 5, and we are left with [5, 5].
 * We merge [5, 5] for a cost of 10, and we are left with [10].
 * The total cost was 20, and this is the minimum possible.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: stones = [3,2,4,1], K = 3
 * Output: -1
 * Explanation: After any merge operation, there are 2 piles left, and we can't
 * merge anymore.  So the task is impossible.
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: stones = [3,5,1,2,6], K = 3
 * Output: 25
 * Explanation: 
 * We start with [3, 5, 1, 2, 6].
 * We merge [5, 1, 2] for a cost of 8, and we are left with [3, 8, 6].
 * We merge [3, 8, 6] for a cost of 17, and we are left with [17].
 * The total cost was 25, and this is the minimum possible.
 * 
 * 
 * 
 * 
 * Note:
 * 
 * 
 * 1 <= stones.length <= 30
 * 2 <= K <= 30
 * 1 <= stones[i] <= 100
 * 
 * 
 * 
 * Digestion:
 * Reverse thinking: instead of considering first remove K
 * consecutive piles of stone, think that eventually the final
 * move will be a K-way merge of K pile of stones.
 */
class Solution {
   int k; int infty;
   vector<int> s; int n;

   vector<int> ps;
   vector<vector<vector<int>>> dp;

   int sol(int i, int j, int l) {
      assert(i <= j && i >= 0 && j < n);

      int &ans = dp[i][j][l];
      if (ans != -1) {
         return ans;
      }

      if (l > 1) {
         ans = infty;
         for (int h = i; h < j; ++h) {
            ans = min(ans, sol(i, h, l - 1) + sol(h + 1, j, 1));
         }
      } else {
         int len = j - i + 1;
         if (len < k) {
            ans = (len == 1) ? 0 : infty;
         } else if (len == k) {
            ans = ps[j + 1] - ps[i];
         } else {
            ans = ps[j + 1] - ps[i] + sol(i, j, k);
         }
      }

      return ans;
   }
public:
    int mergeStones(vector<int>& stones, int K) {
        k = K; n = stones.size(); swap(s, stones);
        dp.resize(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));

        ps.push_back(0);
        for (int i = 0; i < n; ++i) {
           ps.push_back(ps.back() + s[i]);
        }

        infty = n * ps.back();

        int ret = sol(0, n - 1, 1);
        return ret >= infty ? -1 : ret;
    }
};


/*
TESTS
[3,2,4,1]
3
[3,2,4,1]
2
[3,5,1,2,6]
3
[29,74,10,11,15,81,52,24,58,76,59,19,66,26,87,47,33,96,2]
7
*/
