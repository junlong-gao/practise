/*
 * [805] Escape The Ghosts
 *
 * https://leetcode.com/problems/escape-the-ghosts/description/
 *
 * algorithms
 * Medium (49.10%)
 * Total Accepted:    3.6K
 * Total Submissions: 7.3K
 * Testcase Example:  '[[1,0],[0,3]]\n[0,1]'
 *
 * You are playing a simplified Pacman game. You start at the point (0, 0), and
 * your destination is (target[0], target[1]). There are several ghosts on the
 * map, the i-th ghost starts at (ghosts[i][0], ghosts[i][1]).
 * 
 * Each turn, you and all ghosts simultaneously *may* move in one of 4 cardinal
 * directions: north, east, west, or south, going from the previous point to a
 * new point 1 unit of distance away.
 * 
 * You escape if and only if you can reach the target before any ghost reaches
 * you (for any given moves the ghosts may take.)  If you reach any square
 * (including the target) at the same time as a ghost, it doesn't count as an
 * escape.
 * 
 * Return True if and only if it is possible to escape.
 * 
 * 
 * Example 1:
 * Input: 
 * ghosts = [[1, 0], [0, 3]]
 * target = [0, 1]
 * Output: true
 * Explanation: 
 * You can directly reach the destination (0, 1) at time 1, while the ghosts
 * located at (1, 0) or (0, 3) have no way to catch up with you.
 * 
 * 
 * 
 * Example 2:
 * Input: 
 * ghosts = [[1, 0]]
 * target = [2, 0]
 * Output: false
 * Explanation: 
 * You need to reach the destination (2, 0), but the ghost at (1, 0) lies
 * between you and the destination.
 * 
 * 
 * 
 * Example 3:
 * Input: 
 * ghosts = [[2, 0]]
 * target = [1, 0]
 * Output: false
 * Explanation: 
 * The ghost can reach the target at the same time as you.
 * 
 * 
 * Note:
 * 
 * 
 * All points have coordinates with absolute value <= 10000.
 * The number of ghosts will not exceed 100.
 * 
 * 
 * Digestion:
 * Let T be the destination. 
 * Ghost g can intercept player p if and only if the shortest distance from
 * g to T is less or equal to distance from p to T.
 * Proof.
 * Start with "only if" part:
 *  for all possible path from start to T, there exists a node along the path
 *  such that g can meet p only if the dist(S, T) >= dist(g, T).
 * Which is the same as:
 *  if dist(S, T) < dist(g, T), then there exists a path from start to T such
 *  that g cannot meet p at any point of the path.
 *
 * Induction on path length dist(S, T):
 *  when dist = 1, trivial.
 *  let's say this is true for path length n > 1, then in order for p to reach
 *  T, it must go through an adjacent point x of T. Then dist(S, x) = n - 1.
 *  On the other hand, dist(x, g) >= dist(T, g) - 1 > dist(S, T) - 1 = dist(S, x) = n - 1
 *  (the first is because dist(a, b) = |a.r - b.r| + |a.c - b.c|).
 *  Then induction follows as we can reach x without being intercepted, we can
 *  then go from x to T without being intercepted because g must arrive later
 *  than us due to n < dist(T, g).
 *  
 *
 * For the if part, the ghost can simply reach T no later than us and wait there.
 *  
 * This completes the proof.
 *  
 * The implementation is trivially go through all ghost and make sure their
 * distance is larger than us.
 */
class Solution {
public:
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        auto dist = [&](const vector<int> p) {
           return abs(target[0] - p[0]) + abs(target[1] - p[1]);
        };

        int dist0 = dist({0, 0});

        for (const auto &g : ghosts) {
           if (dist(g) <= dist0) return false;
        }

        return true;
    }
};


/*
TESTS
[[1, 0], [0, 3]]
[0, 1]
[[1, 0]]
[2, 0]
[[2, 0]]
[1, 0]
*/
