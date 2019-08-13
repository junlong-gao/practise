class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> s;
        for (int i = 0; i < asteroids.size(); ++i) {
            if (s.empty() || asteroids[i] > 0) {
                s.push_back(asteroids[i]);
                continue;
            }
            while (!s.empty() && s.back() > 0 && s.back() < -asteroids[i]) {
                s.pop_back();
            }
            
            if (!s.empty() && s.back() + asteroids[i] == 0) {
                s.pop_back();
                continue;
            }
            if (s.empty() || s.back() < 0) {
                s.push_back(asteroids[i]);
            }
        }
        return s;
    }
};
