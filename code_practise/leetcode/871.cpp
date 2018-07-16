class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        multiset<int, std::greater<int>> unused;
        int left = startFuel, prevLoc = 0, prevFill = 0;
        stations.push_back({target, 0});
        for (const auto & s : stations) {
            left -= s[0] - prevLoc;
            if (prevLoc > 0) { 
                unused.insert(prevFill);
            }
            while (left < 0 && unused.size() > 0) {
                left += *unused.begin();
                unused.erase(unused.begin());  
            }
            
            if (left < 0) return -1;
            prevFill = s[1];
            prevLoc = s[0];
        }
        return stations.size() - 1 - unused.size();
    }
};