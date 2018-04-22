/*
It eventually becomes linking nodes with minimal edges, where each node represents
someone's balance.

The problem is it does not specify input size. Quick googling shows it is NPC:
http://www.mathmeth.com/tom/files/settling-debts.pdf
https://en.wikipedia.org/wiki/3-partition_problem

So bruteforce with opt is the only viable option. Backtrack to iterate all possible
linking and find the optimial.

The key observation for optimization is, when looking at node i, you only need to
consider moving *all* its balance to some unvisited node j. This is because the number
of edges will be the same whether edges are coming from/to node i (some linking to j, some linking to others)
or node j (from i linking to others transferred to originating from node j).

Also, when considering transfer all balance from node i to node j, it will yield the same
result when considering transfering balance from node i to node k where j and k have the same balance.
*/
class Solution {
    int n;
    vector<int> bals;
public:
    // search starting from node
    // backtrack
    int search(int node) {
        //cout << node << endl;
        //cout << bals[node] << endl;
        int ret = INT_MAX;
        while (node < n && bals[node] == 0) node++;
        if (node == n) return 0;
        assert(node != n - 1);
        
        // node is now the first non-0 bals to settle.
        int &v = bals[node];

        int last = 0;
        for (int i = node + 1; i < n; ++i) {
            if (bals[i] == last || bals[i] * v >= 0) continue;
            // consider linking v and i to clear bals[i]
            bals[i] += v;
            ret = std::min(ret, 1 + search(node + 1));
            // backtrack
            bals[i] -= v;
            
            // optimization: linking v with the same bals[i] by completely
            // transfer balance from v onto bals[i] will yield the same result.
            last = bals[i];
        }
        return ret;
    }
    
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> nodes;
        for (int i = 0; i < transactions.size(); ++i) {
            nodes[transactions[i][0]] -= transactions[i][2];
            nodes[transactions[i][1]] += transactions[i][2];
        }
        
        for (auto pr : nodes) {
            if (pr.second != 0) {
                bals.push_back(pr.second);
            }
        }
        n = bals.size();
        return search(0);
    }
};
