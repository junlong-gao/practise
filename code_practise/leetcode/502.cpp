/*
 * > lcg 502
 *   ✔ Accepted
 *   ✔ 31/31 cases passed (64 ms)
 *   ✔ Your runtime beats 30.41 % of cpp submissions
 *
 * [502] IPO
 *
 * https://leetcode.com/problems/ipo/description/
 *
 * algorithms
 * Hard (36.58%)
 * Total Accepted:    6.8K
 * Total Submissions: 18.6K
 * Testcase Example:  '2\n0\n[1,2,3]\n[0,1,1]'
 *
 *
 * Suppose LeetCode will start its IPO soon. In order to sell a good price of
 * its shares to Venture Capital, LeetCode would like to work on some projects
 * to increase its capital before the IPO. Since it has limited resources, it
 * can only finish at most k distinct projects before the IPO. Help LeetCode
 * design the best way to maximize its total capital after finishing at most k
 * distinct projects.
 *
 *
 *
 * You are given several projects. For each project i, it has a pure profit Pi
 * and a minimum capital of Ci is needed to start the corresponding project.
 * Initially, you have W capital. When you finish a project, you will obtain
 * its pure profit and the profit will be added to your total capital.
 *
 *
 *
 * To sum up, pick a list of at most k distinct projects from given projects to
 * maximize your final capital, and output your final maximized capital.
 *
 *
 * Example 1:
 *
 * Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].
 *
 * Output: 4
 *
 * Explanation: Since your initial capital is 0, you can only start the project
 * indexed 0.
 * ⁠            After finishing it you will obtain profit 1 and your capital
 * becomes 1.
 * ⁠            With capital 1, you can either start the project indexed 1 or
 * the project indexed 2.
 * ⁠            Since you can choose at most 2 projects, you need to finish the
 * project indexed 2 to get the maximum capital.
 * ⁠            Therefore, output the final maximized capital, which is 0 + 1 +
 * 3 = 4.
 *
 *
 *
 * Note:
 *
 * You may assume all numbers in the input are non-negative integers.
 * The length of Profits array and Capital array will not exceed 50,000.
 * The answer is guaranteed to fit in a 32-bit signed integer.
 *
 *
 * Digestion:
 * Read the spec.
 */
class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
       auto pcomp = [&](const int l, const int r) {
          if (Profits[l] != Profits[r]) return Profits[l] < Profits[r]; // XXX:uniqueness, otherwise same key will be overriden
          return l < r;
       };

       auto ccomp = [&](const int l, const int r) {
          if (Capital[l] != Capital[r]) return Capital[l] < Capital[r];
          return l < r;
       };

       set<int, decltype(pcomp)> doable(pcomp);
       set<int, decltype(ccomp)> undoable(ccomp);
       int n = Profits.size();

       for (int i = 0; i < n; ++i) {
          if (Capital[i] <= W) {
             doable.insert(i);
          } else {
             undoable.insert(i);
          }
       }


       while (k-- > 0 && !doable.empty()) {
          W += Profits[*doable.rbegin()];
          doable.erase(*doable.rbegin());
          for (auto it = undoable.begin(); it != undoable.end();) {
             if (Capital[*it] > W) break;
             doable.insert(*it);
             it = undoable.erase(it);
          }
       }

       return W;
    }
};


/*
TESTS
3
0
[3,10,11, 1000]
[0,1,3, 12]
1
0
[3,10,11, 1000]
[0,1,3, 12]
10
0
[3,10,11, 1000]
[0,1,3, 12]
*/
