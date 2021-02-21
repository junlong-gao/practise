/*
1. Observe that each strategy corresponds to adding + - and () to the stone sequence.
   for example, 2, 4, 5 -> +2 -4 +5 -> +2 -(-4 +5)
   note that this is not unique
2. From here we have 2 approaches:
   2.a expand all (), and make it an assigment problem.
   2.b rearrange the sequence into (s1 + s2 + s3) - (s4 + s5 + s6)
       and find the largest sum that can reach half total sum.

2.a, do not define state as particular assigments -> exponetial (state of
assigment -> sum). Instead, note that possible sums do not form a large
search space, turn it into a reachablility problem: ((sum, state of
collection) -> reachable). Now to compute reachability, we do not need the
state of the collection, just the collection itself and recurse.
*/
class Solution {
    vector<unordered_map<int, int>> dp;
    int search(int sum, int idx, vector<int> &stones) {
        if (dp[idx].count(sum)) {
            return dp[idx][sum];
        }
        
        int &ret = dp[idx][sum];
        if (idx == 0) {
            return ret = (sum == stones[idx]) || (sum == 0 - stones[idx]);
        } else {
            ret = max(search(sum + stones[idx], idx - 1, stones),
                      search(sum - stones[idx], idx - 1, stones));
            return ret;
        }
    }
public:
    int lastStoneWeightII(vector<int>& stones) {
        dp.resize(stones.size());
        
        int s = 0;
        while (true) {
            int ret = search(s, stones.size() - 1, stones);
            if (ret) {
                return s;
            }
            s++;
        }
    }
};