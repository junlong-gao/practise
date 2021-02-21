class Solution {
    /*
    Let set be a collection of none zero balances that sum to 0. It has a solution of |set| - 1. This
    can constructed by align all elements in a line (in any order), process from left to right,
    and transfer all balances from left to the right one or the other direction depending on
    which one has positive balance.

    Now if we can break the set into 2 parts, subset1 has sum 0 and (hence) subset2 has sum 0. Then both of
    them will have a solution |subset| - 1, giving the total solution |set| - 2 which is better than |set| - 1;

    In general, we need to break set into disjoint subsets that each of them has sum 0, and none of them
    can be further broken, then we have an optimal solution |set| - # broken subsets.

    Recursive structure dp[set] = max number of zero subsets it can break into:
    dp[{}] = 0; (empty set does not count)
    dp[set] = if (sum(set) == 0) max_{ele in set} {dp{sub \ ele} + 1} (*)
              else max_{ele in set}{dp[sub \ ele]} (**)
              0 if set is empty
    (*) to arrive at contradiction, note that adding ele to a subproblem's residue will increase size by 1
    (**) to arrive at contradiction, say we can add ele to some of the residue to form a new zero subset, then
         the remaining residue set must not be empty (since total sum is not 0). and this yields a better subproblem
         solution by considering removing any of the remaining residue from the original set.
    */
    unordered_map<int, int> dp;
    int search(const vector<int> &bal, int set, int sum) {
        if (set == 0) return 0;
        if (dp.count(set)) return dp[set];

        int &ret = dp[set];
        if (sum == 0) {
            ret = 1;
        } else {
            ret = 0;
        }

        for (int i = 0; i < bal.size(); ++i) {
            if (set & (1 << i)) {
                int removedI = set & (~(1<<i));
                if (sum == 0) {
                    ret = max(ret, search(bal, removedI, sum - bal[i]) + 1);
                } else {
                    ret = max(ret, search(bal, removedI, sum - bal[i]));
                }
            }
        }

        return ret;
    }
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> tmp;
        for (auto &t : transactions) {
            tmp[t[0]] += t[2];
            tmp[t[1]] -= t[2];
        }
        vector<int> bals;
        for (auto pr : tmp) {
            if (pr.second) {
                bals.push_back(pr.second);
            }
        }
        return bals.size() - search(bals, (1 << bals.size()) - 1, 0);
    }
};