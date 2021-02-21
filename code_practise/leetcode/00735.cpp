class Solution {
public:
    vector<int> asteroidCollision(vector<int>& as) {
        vector<int> ret;
        for (int i = 0; i < as.size(); ++i) {
            if (as[i] > 0) {
                ret.push_back(as[i]);
            } else {
                while (!ret.empty() && ret.back() > 0 && ret.back() < -as[i]) {
                    ret.pop_back();
                }
                // 3 cases: as[i] destroyed, both destroyed, last one destroyed
                if (!ret.empty() && ret.back() > 0 && ret.back() > -as[i]) {
                    //
                } else if (!ret.empty() && ret.back() > 0 && ret.back() == -as[i]) {
                    ret.pop_back();
                } else {
                    ret.push_back(as[i]);
                }
            }
        }

        return ret;
    }
};