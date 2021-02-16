class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> refcount;
        for (auto e : nums) refcount[e]++;

        map<int, vector<int>> index;
        for (auto pr : refcount) {
            index[pr.second].push_back(pr.first);
        }

        auto it = index.rbegin();
        vector<int> ret;
        while (ret.size() < k && it != index.rend()) {
            auto itt = it->second.begin();
            while (ret.size() < k && itt != it->second.end()) {
                ret.push_back(*itt);
                itt++;
            }
            it++;
        }

        return ret;
    }
};