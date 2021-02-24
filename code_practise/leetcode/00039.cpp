class Solution {
    void search(
    vector<int> &nums,
    int idx,
    int target,
    vector<int> &sofar,
    vector<vector<int>> *output) {
        if (target < 0) return;
        if (idx == nums.size()) {
            if (target == 0) {
                output->push_back(sofar);
            }
            return;
        }
        
        search(nums, idx + 1, target, sofar, output);

        sofar.push_back(nums[idx]);
        search(nums, idx, target - nums[idx], sofar, output);
        sofar.pop_back();
       
        return;
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ret;
        vector<int> sofar;
        search(candidates, 0, target, sofar, &ret);
        return ret;
    }
};