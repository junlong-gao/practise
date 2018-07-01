class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        vector<int> sum{0};
        for (auto e : A) {
            sum.push_back(sum.back() + e);
        }
        deque<int> cand;
        int best = INT_MAX;
        for (int i = 0; i < sum.size(); ++i) {
            while(cand.size() && sum[i] - sum[cand.front()] >= K) {
                best = min(best, i - cand.front());
                cand.pop_front();
            }
            
            while (cand.size() && sum[cand.back()] >= sum[i]) {
                cand.pop_back();
            }
            cand.push_back(i);
        }
        return best == INT_MAX ? -1 : best;
    }
};

/*
[0, 2, 1, 3]
{0}
{0, 1}
{0, 2}
{2, 3} best = 3 - 0 = 3

 0  1  2  3  4  5
[0, 1, 3, 6, 3, 4]
K = 3
{0}
{0, 1}
{1, 2} best = 2
{3} best = 1
*/
