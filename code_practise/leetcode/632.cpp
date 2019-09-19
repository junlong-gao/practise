class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        map<int, vector<int>> refcount;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums[i].size(); ++j) {
                refcount[nums[i][j]].push_back(i);
            }
        }
        unordered_map<int, int> sofar;
        
        int l = refcount.begin()->first; 
        int r = prev(refcount.end())->first;
        
        for (auto e = refcount.begin(), f = refcount.begin();
             e != refcount.end(); ++e) {
            
             for (auto idx : e->second) { sofar[idx] ++;}
            
             while (sofar.size() == nums.size()) {
                if (e->first - f->first < r - l) { l = f->first; r = e->first; }
                for (auto idx : f->second) { 
                    sofar[idx] --;
                    if (sofar[idx] == 0) { sofar.erase(idx); }
                }
                f++;
            }
            
        }
        
        return {l, r};
    }
};