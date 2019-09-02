class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        for (int i = 0; i + 1 < nums.size(); ++i) {
            if (nums[i] == 0 && nums[i + 1] == 0) {
                return true;
            }
        }
            
        if (k == 0) { return false; }
        
        if (k < 0) k = -k; 
        
        unordered_map<int, vector<int>> mp;
        mp[0] = {-1};
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            mp[sum % k].push_back(i);
            //cout << sum % k << " " << i << endl;
        }
        
        for (auto & pr : mp) {
            for (int i = 1; i < pr.second.size(); ++i) {
                if (pr.second[i] - pr.second[0] >= 2) return true;
            }
        }
        
        return false;
    }
};
