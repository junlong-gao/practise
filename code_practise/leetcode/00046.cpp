class Solution {
    void search(deque<int> &pfx, vector<int> &sofar, vector<vector<int>> *output) {
        if (pfx.empty()) {
            output->push_back(sofar);
        } else {
            for (int i = 0; i < pfx.size(); ++i) {
                sofar.push_back(pfx.front());
                pfx.pop_front();
                
                search(pfx, sofar, output);
                
                pfx.push_back(sofar.back());
                sofar.pop_back();
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
       deque<int> tmp(nums.begin(), nums.end());
        vector<vector<int>> output;
        vector<int> sofar;
        search(tmp, sofar, &output);
        
        return output;
    }
};