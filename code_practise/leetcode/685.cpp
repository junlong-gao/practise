/*
adding one edge will result in existing two nodes u and v such that path from u to v is not unique.


if we don't have a node with 2 indegree, there must be a cycle (so every pair of nodes have
non-unique path). this is easy and we can remove any edge we found on the cycle.

if we have a node having 2 indegree, we cannot delete either one of the edges to make sure 
paths between all pair of nodes are unique:

1                 1 ---
|                 |    |
v                 v    v
2 <-> 3           2 -->3
for the left we must delete {3, 2}, for the right we can delete either {2, 3} or {1, 3}

the trick is we try to delete the second edge of the found 2de edges first. 
for the left case:
1                   1 --> 0
|
v
2 -> 3 -> 0         2 <-> 3
depending on which of the edges {1, 2} and {3, 2} we see first in the input.

for the right case:

      1 ---           1 ---> 0
      |    |          |
      v    v          v
0 <-- 2    3          2 ---> 3
depending on which of the edges {2, 3} and {1, 3} we see first in the input.


now if we find that after deleting one of the edges in 2de, we can still
find a non-unique path (right graph), then we automatically conclude we
have deleted the wrong edge and we should delete the undeleted one.

if we find all paths between two nodes are unique, then it is the deleted 
edge caused the non-unique path.
*/
class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> p(n + 1, 0), undeleted, deleted;
        for (auto& edge : edges) {
            if (p[edge[1]] == 0) {
                p[edge[1]] = edge[0];
            } else {
                undeleted = {p[edge[1]], edge[1]};
                deleted = edge;
                edge[1] = 0; // 
            }
        }
        
        // check path uniqueness after adding each edge
        // by checking each node has a unique path to its highest ancestor so far.
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
        }
        
        for (auto& edge : edges) {
            int a0 = edge[0];
            while (p[a0] != a0) {
                a0 = p[a0];
            }
            int a1 = edge[1];
            while (p[a1] != a1) {
                a1 = p[a1];
            }
            if (a0 == a1) {
                // non unique path: a0->...->edge0->edge1 and a0->...->edge1
                // we did not found 2de node, so this non unique path comes from cycle
                if (undeleted.empty()) return edge;
                // the edge we deleleted is not right, we still have non-unique path, should
                // delete the undeleted one.
                return undeleted;
            }
            p[edge[1]] = edge[0];
        }
        // paths between all nodes are unique, we have deleted the right edge:
        assert(deleted.size() == 2);
        return deleted;
    }
};
