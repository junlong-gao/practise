class NumArray {
    vector<int> b;
    vector<int> v;
    int n;
public:
    NumArray(vector<int> nums) {
        n = nums.size();
        swap(v, nums);
        b.resize(n + 1);
        for (int i = 0; i < n; ++i) {
            update(i, nums[i]);
        }
    }
    
    void update(int i, int val) {
        int idx = i + 1;
        int u = val - v[i];
        v[i] = u;
        while (idx <= n) {
            b[idx] += u;
            idx += idx & (-idx);
        }
    }
    
    int sumRange(int i, int j) {
        int ret = 0; idx = i + 1;
        while (idx) {
            ret += b[idx];
            idx -= idx & (-idx);
        }
        return ret;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
