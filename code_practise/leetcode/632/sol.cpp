class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        using it_t = vector<int>::iterator;
        using pr_t = pair<it_t, it_t>;
        const int int_max = numeric_limits<int>::max() - 1;
        
        int l = int_max, r = -int_max;
        if(nums.size() == 1) return {nums[0].front(), nums[0].back()};
        auto order = [](const pr_t& ll, const pr_t& rr) -> bool{
            return *(ll.first) > *(rr.first);
        };
        
        priority_queue<pr_t, vector<pr_t>, decltype(order)> q(order);
        for(auto& list : nums){
            l = min(l, list.front());
            r = max(r, list.front());
            q.emplace(list.begin(), list.end());
        }
        //cout << " ---- " << endl;
        int ans = r-l;
        vector<int> ret{l, r};
        while(true){
            auto cur = q.top();
            q.pop();
            ++(cur.first);
            if(cur.first == cur.second) break;
            
            q.push(cur);
            l = *(q.top().first);
            r = std::max(r, *(cur.first));
            if(r - l < ans){
                ret[0] = l;
                ret[1] = r;
                ans = r - l;
            }
        }
        return ret;
        
    }
};