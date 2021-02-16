// simulation
class Solution {
    struct ent {
       int workerIdx; int bikeIdx;
    };
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        map<int, vector<ent>> ds;
        // (worker, bike)
        for (int i = 0; i < workers.size(); ++i) {
            for (int j = 0; j < bikes.size(); ++j) {
                ds[abs(workers[i][0] - bikes[j][0]) + abs(workers[i][1] - bikes[j][1])].push_back(ent{i, j});
            }
        }
        
        vector<int> assignment(workers.size());
        vector<bool> assignedWorker(workers.size(), false), assignedBike(bikes.size(), false);
        for (auto it = ds.begin(); it != ds.end(); ++it) {
            for (auto & pr:it->second) {
                if (assignedWorker[pr.workerIdx] || assignedBike[pr.bikeIdx]) {
                    continue;
                }
                assignment[pr.workerIdx] = pr.bikeIdx;
                assignedWorker[pr.workerIdx] = true;
                assignedBike[pr.bikeIdx] = true;
            }
        }
        return assignment;
    }
};