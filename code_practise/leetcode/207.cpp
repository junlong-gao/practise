/*
 * @lc app=leetcode id=207 lang=cpp
 *
 * [207] Course Schedule
 *
 * https://leetcode.com/problems/course-schedule/description/
 *
 * algorithms
 * Medium (38.74%)
 * Total Accepted:    240.7K
 * Total Submissions: 621.4K
 * Testcase Example:  '2\n[[1,0]]'
 *
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 *
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 *
 * Given the total number of courses and a list of prerequisite pairs, is it
 * possible for you to finish all courses?
 *
 * Example 1:
 *
 *
 * Input: 2, [[1,0]]
 * Output: true
 * Explanation: There are a total of 2 courses to take.
 * To take course 1 you should have finished course 0. So it is possible.
 *
 * Example 2:
 *
 *
 * Input: 2, [[1,0],[0,1]]
 * Output: false
 * Explanation: There are a total of 2 courses to take.
 * To take course 1 you should have finished course 0, and to take course 0 you
 * should
 * also have finished course 1. So it is impossible.
 *
 *
 * Note:
 *
 *
 * The input prerequisites is a graph represented by a list of edges, not
 * adjacency matrices. Read more about how a graph is represented.
 * You may assume that there are no duplicate edges in the input
 * prerequisites.
 *
 *
 */
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // node1 -> node2 iff take node 1 depends on node 2
        vector<unordered_set<int>> g(numCourses);
        // each node's in degree, node 2 in-degree ++
        vector<int> in(numCourses, 0);

        vector<bool> visited(numCourses, false);

        for (auto & e : prerequisites) {
           // e: (node2, node1)
           g[e[1]].insert(e[0]);
           in[e[0]]++;
        }

        deque<int> q;
        int courseCanTake = 0;

        // initial set of course that you can take
        for (int n = 0; n < numCourses; ++n) {
           if (in[n] == 0) {
              q.push_back(n);
              visited[n] = true;
              courseCanTake++;
           }
        }

        while (!q.empty()) {
           auto n = q.front(); q.pop_front();
           for (auto & d : g[n]) {
              if (visited[d]) continue;
              in[d]--;
              if (in[d] == 0) {
                 q.push_back(d);
                 visited[d] = true;
                 courseCanTake++;
              }
           }
        }

        return courseCanTake == numCourses;
    }
};

/*
TESTS
2
[[1,0]]
2
[[1,0],[0,1]]
4
[[3,0],[0,1], [1, 2]]
4
[[3,0],[0,1], [1, 2], [2, 3]]
*/
