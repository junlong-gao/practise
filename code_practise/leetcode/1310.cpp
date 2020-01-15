class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> pfx{0};
        for (int i = 0; i < arr.size(); ++i) {
            pfx.push_back(pfx.back() ^ arr[i]);
        }

        vector<int> ret;
        for (auto & q : queries) {
            ret.push_back(pfx[q[1] + 1] ^ pfx[q[0]]);
        }

        return ret;
    }
};