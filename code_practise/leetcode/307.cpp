class NumArray {
    vector<int> b;
    vector<int> v;
    int n;
public:
    NumArray(vector<int> nums) {
        n = nums.size();
        b.resize(n + 1, 0);
        v.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            update(i, nums[i]);
        }
    }
    
    void update(int i, int val) {
        int idx = i + 1;
        int u = val - v[i];
        v[i] = val;
        while (idx <= n) {
            b[idx] += u;
            idx += idx & (-idx);
        }
    }
    
    int sum(int i) {
        int ret = 0, idx = i + 1;
        while (idx) {
            ret += b[idx];
            idx -= idx & (-idx);
        }
        return ret;
    }
    
    int sumRange(int i, int j) {
        int l = i ? sum(i - 1) : 0;
        int r = sum(j);
        return r - l;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
