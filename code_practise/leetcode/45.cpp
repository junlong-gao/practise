/*
> leetcode submit 45.cpp
  ✔ Accepted
  ✔ 92/92 cases passed (15 ms)
  ✔ Your runtime beats 23.77 % of cpp submissions
 * [45] Jump Game II
 *
 * https://leetcode.com/problems/jump-game-ii/description/
 *
 * algorithms
 * Hard (26.14%)
 * Total Accepted:    112.3K
 * Total Submissions: 430.1K
 * Testcase Example:  '[0]'
 *
 *
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.
 *
 *
 * Each element in the array represents your maximum jump length at that
 * position.
 *
 *
 * Your goal is to reach the last index in the minimum number of jumps.
 *
 *
 *
 * For example:
 * Given array A = [2,3,1,1,4]
 *
 *
 * The minimum number of jumps to reach the last index is 2. (Jump 1 step from
 * index 0 to 1, then 3 steps to the last index.)
 *
 *
 *
 * Note:
 * You can assume that you can always reach the last index.
 *
 * Digestion:
 * Imagine each node extend nums[node] edges to the next nodes.
 * Then this becomes a min distance graph search, which can be trivially
 * solved via BFS (each edge weight 1).
 *
 * This can TLE as BFS is O(E), where E can be O(n^2) (each node extend
 * n/2 edges).
 *
 * Running BFS in head shows the min dist on each node increases at most by 1
 * from left to right.
 *
 * len:  0 1 2 3 4
 * nums: 2 1 3 2 1
 * dist: 0 1 1 2 2
 *
 * A enqueue group in BFS is a set of nodes share the same dist. That is, a
 * boundary. In BFS, enqueue can be viewed in terms of groups: a group
 * dequeued, all sharing same dist, and they enqueue a new group, with new same
 * dist (increased by 1).
 *
 * The trick is the whole graph is topologically sorted. We find that all
 * elements, if ordered by the time they are enqueued, is exactly the same
 * sequence of the original nums[].
 *
 * Combining the above two observation, we conclude we can perform BFS by:
 * Using the original nums[] as the queue and scanning from left to right
 * as the head of the queue. There is no need to repeatedly check a node is
 * reached or not (as number of edges can be huge). We view the elements scanned
 * in terms of enqueued groups in BFS, and for the same group they share the same
 * dist. We identify a new group by maintaining the current group boundary:
 *
 * A1 A2 A3 B1 B2 B3 B4 B5
 *       X              X
 *
 * - group A share all same dist. A3 is the last element in the boundary
 * - group B share all same dist = dist_A + 1. B5 is the last element in the
 *   boundary (the furthest reachable from group A)
 * - if we arrive at A3, we know we have finished processing group A and
 *   we have entered group B, increase dist.
 * - To make sure we know A3 and B5, we maintain curBoundary and nextBoundary.
 *   nextBoundary gets updated when we go from A1 to A3, and will point at
 *   position B5 we processed A3. And because curBoundary points at A3, we
 *   know we have completed the group A, and we move curBoundary to B5 as we
 *   enter group B.
 * - Initially, enqueue the first node and the curBoundary is nums[0]. Because
 *   we immediately dequeue nums[0], the nextBoundary is set to be curBoundary
 *
 * The BFS terminates when nextBoundary exceeds nums.size() - 1.
 *
 */
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() <= 1) return 0;

        int dist = 1; int curBoundary = nums[0]; int nextBoundary = curBoundary;

        for (int i = 1; i < nums.size(); ++i) {
           if (curBoundary >= nums.size() - 1) break;

           nextBoundary = std::max(nextBoundary, i + nums[i]);
           if (i == curBoundary) { dist++; curBoundary = nextBoundary; }
        }

        return dist;
    }
};


/*
TESTS
[]
[1]
[1, 1]
[1, 2]
[2,2,2,2,2,2,2,2,10,2,2]
[2,2,100,2,2,2,2,2,2,2,10,2,2]
*/
