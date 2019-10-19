class Solution {
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        map<int, vector<pair<int, int>>> allDist;
        for (int i = 0; i < workers.size(); ++i) {
            for (int j = 0; j < bikes.size(); ++j) {
                int d = abs(workers[i][0] - bikes[j][0]) +
                            abs(workers[i][1] - bikes[j][1]);
                allDist[d].push_back(make_pair(i, j));
            }
        }
        
        vector<int> ret(workers.size());
        unordered_set<int> assignedWorker, assignedBike;
        for (auto it = allDist.begin(); it != allDist.end(); ++it) {
            for (const auto& pr : it->second) {
                if (assignedWorker.count(pr.first) ||
                    assignedBike.count(pr.second)) {
                    continue;
                }
                ret[pr.first] = pr.second;
                assignedWorker.insert(pr.first);
                assignedBike.insert(pr.second);
            }
        }
        return ret;
    }
};
