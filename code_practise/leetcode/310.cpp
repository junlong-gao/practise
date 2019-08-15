class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1) return {0};
        unordered_map<int, unordered_set<int>> g;
        for(auto& pr: edges){
            g[pr[0]].insert(pr[1]);
            g[pr[1]].insert(pr[0]);
        }
        while(g.size() > 2){
            auto it = g.begin();
            vector<pair<int, int>> to_remove;
            while(it!=g.end()){
                if(it->second.size() == 1){
                    to_remove.emplace_back(*(it->second.begin()), it->first);
                    it = g.erase(it);
                }else{
                    it++;
                }
            }
            for(auto& pr: to_remove){
                g[pr.first].erase(pr.second);
            }
        }
        vector<int> ret;
        for(auto& pr: g){
            ret.push_back(pr.first);
        }
        return ret;
    }
};
