class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<int> st, et;
        for (auto & i : intervals) {
            st.push_back(i[0]);
            et.push_back(i[1]);
        }
        
        sort(st.begin(), st.end());
        sort(et.begin(), et.end());
        int sp = 0; int ep = 0;
        int ret = 0;
        while (sp < st.size()) {
            if (st[sp] < et[ep]) {
                ret++;
            } else {
                ep++;
            }
            sp++;
        }
        return ret;
    }
};
