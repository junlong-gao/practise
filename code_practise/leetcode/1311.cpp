class Solution {
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        deque<int> q{id}; unordered_set<int> visited; unordered_map<string, int> ret;
        visited.insert(id);
        while (q.size()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                for (int f : friends[q.front()]) {
                    if (visited.count(f)) continue;
                    q.push_back(f); visited.insert(f);
                }
                q.pop_front();
            }
            
            level--;
            if (level == 0) {
                for (auto f : q) {
                    for (auto &v : watchedVideos[f]) {
                        ret[v]++;
                    }
                }
                vector<pair<string, int>> tmp;
                for (auto pr : ret) {
                    tmp.push_back(pr);
                }
                sort(tmp.begin(), tmp.end(), [](const pair<string, int>& l, const pair<string, int>& r) {
                    if (l.second != r.second) {
                        return l.second < r.second;
                    }
                    return l.first < r.first;
                });
                vector<string> r;
                for (int i = 0; i < tmp.size(); ++i) {
                    r.push_back(tmp[i].first);
                }
                return r;
            }
        }
        return {};
    }
};