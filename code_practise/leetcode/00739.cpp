class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> s;
        vector<int> ret(T.size(), 0);
        for (int i = 0; i < T.size(); ++i) {
            while (s.size() > 0 && T[i] > T[s.back()]) {
                ret[s.back()] = i - s.back();
                s.pop_back();
            }
            s.push_back(i);
        }
        return ret;
    }
};