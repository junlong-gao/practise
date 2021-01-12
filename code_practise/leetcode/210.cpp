class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegrees(numCourses, 0);
        vector<vector<int>> g(numCourses);
        for (auto &e : prerequisites) {
            g[e[1]].push_back(e[0]);
            indegrees[e[0]]++;
        }
        deque<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegrees[i] == 0) {
                q.push_back(i);
            }
        }
        vector<int> ret;
        while (q.size()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                auto top = q.front();
                q.pop_front();
                ret.push_back(top);
                for (auto n : g[top]) {
                    indegrees[n]--;
                    if (indegrees[n] == 0) {
                        q.push_back(n);
                    }
                }
            }
        }
        if (ret.size() == numCourses) {
            return ret;
        }
        return {};
    }
};