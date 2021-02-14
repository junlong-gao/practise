class Solution {
    int count(vector<int> &in, int i, int j) {
        if (i == j) {
            return 0;
        } else if (i == j - 1) {
            return 0;
        }
        
        int mid = (i + j) / 2;
        int ret = count(in, i, mid) + count(in, mid, j);
        
        {
            int li = i, ri = mid;
            while (ri < j) {
                while (li < mid && (long long)in[li] <= (long long)2 * (long long)in[ri]) {
                    li++;
                }
                ret += mid - li;
                ri++;
            }
        }
        
        int lidx = i, ridx = mid;
        vector<int> out;
        while (lidx < mid && ridx < j) {
            if (in[lidx] < in[ridx]) {
                out.push_back(in[lidx++]);
            } else {
                out.push_back(in[ridx++]);
            }
        }
        
        while (lidx < mid) {
            out.push_back(in[lidx++]);
        }
        while (ridx < j) {
            out.push_back(in[ridx++]);
        }
        
        for (int idx = i; idx < j; ++idx) {
            in[idx] = out[idx - i];
        }
        return ret;
    }
public:
    int reversePairs(vector<int>& nums) {
        return count(nums, 0, nums.size());
    }
};