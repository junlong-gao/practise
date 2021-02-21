class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, int> indegree;
        unordered_map<int, vector<int>> g;
        
        for (auto & edge : prerequisites) {
            g[edge[1]].push_back(edge[0]);
            indegree[edge[0]]++;
        }
        
        deque<int> q;
        int count = 0;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push_back(i);
                count++;
            }
        }
        
        while (q.size()) {
            int sz = q.size();
            while (sz-->0) {
                int top = q.front(); q.pop_front();
                for (auto n : g[top]) {
                    indegree[n]--;
                    if (indegree[n] == 0) {
                        q.push_back(n);
                        count++;
                    }
                }
            }
        }
        
        return count == numCourses;
    }
};