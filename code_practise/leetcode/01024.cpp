class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        sort(clips.begin(), clips.end(), [](const vector<int>& l,
                                           const vector<int>& r){
            return l[0] < r[0];
        });
        int i = 0, e = 0;
        int ret = 0;
        while (e < T && i < clips.size()) {
            int ne = e;
            if (clips[i][0] > e) {
                return -1;
            }
            while (i < clips.size() && clips[i][0] <= e) {
                ne = max(ne, clips[i][1]);
                i++;
            }
            ret++;
            e = ne;
        }
        return e >= T ?  ret : -1;
    }
};
