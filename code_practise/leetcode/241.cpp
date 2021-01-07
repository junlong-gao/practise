class Solution {
    vector<int> search(vector<int> &nums, vector<char> &ops,
                      int bi, int ei) {
        if (ei - bi == 1) {
            return {nums[bi]};
        }
        vector<int> ret;
        for (int j = bi; j < ei - 1; ++j) {
            auto l = search(nums, ops, bi, j + 1);
            auto r = search(nums, ops, j + 1, ei);
            for (auto ll : l) {
                for (auto rr : r) {
                    if (ops[j] == '+') {
                        ret.push_back(ll + rr);
                    } else if (ops[j] == '-') {
                        ret.push_back(ll - rr);
                    } else if (ops[j] == '*') {
                        ret.push_back(ll * rr);
                    }
                }
            }
        }
        return ret;
    }
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> nums;
        vector<char> ops;
        int i = 0;
        while (i < input.size()) {
            int j = i;
            while (j < input.size() && std::isdigit(input[j])) {
                j++;
            }
            nums.push_back(stoi(input.substr(i, j - i)));
            if (j < input.size()) {
                ops.push_back(input[j]);
            }
            j++;
            i = j;
        }
        assert(ops.size() + 1 == nums.size());
        return search(nums, ops, 0, nums.size());
    }
};
