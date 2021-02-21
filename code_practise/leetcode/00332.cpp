class Solution {
    /*
    DFS to backtrack a path visiting all edges.
    */
    unordered_map<string, vector<string>> g;
    unordered_map<string, vector<bool>> used;
    bool search(string pos, int rem, vector<string> *output) {
        if (rem == 0) {
            return true;
        }
        
        for (int i = 0; i < g[pos].size(); ++i) {
            if (used[pos][i]) continue;
            
            output->push_back(g[pos][i]);
            used[pos][i] = true;
            if (search(g[pos][i], rem - 1, output)) {
                return true;
            }
            used[pos][i] = false;
            output->pop_back();
        }
        
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto ticket : tickets) {
            g[ticket[0]].push_back(ticket[1]);
        }
        for (auto &pr : g) {
            sort(pr.second.begin(), pr.second.end());
            used[pr.first].resize(pr.second.size(), false);
        }
        vector<string> ret {"JFK"};
        search("JFK", tickets.size(), &ret);
        return ret;
    }
};