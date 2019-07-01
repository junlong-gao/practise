class Solution {
    /*
    Let opt[j] be the largest index i such that P[j] - P[i] >= K,
    where P is the prefix sum (hence P[j] - P[i] is sum [i...j-1], of length
    j - i).
    Let mq[i] be the candidate set for opt[i+1], such that
    1. it is increasing (x < y in mq[i] => P[x] < P[y])
    2. opt[i+1], if exists and is better than all previous solutions, 
       must be in mq[i] (thus not empty), and
       is the largest element x such that P[i + 1] - P[x] >= K
       
     mq[i] is maintained (into mq[i+1]) via poping matched front (smaller
     size) of the set whenever P[i + 1] - mq.front() >= K and poping back 
     whenever P[i + 1] >= mq.back();
     
     proof:
     mq[0], trivial
     assume after maintaining, the invariant no longer holds for mq[i + 1].
     i.e. x = opt[i + 2], assmuing exists and better than previous solutions, 
     is not in mq[i + 1]. note each element is enqueued exactly once,
     to lose x is to pop it in the front or back in previous maintaining.
     1. x is discarded during some previous pop front:
        contradiction: as x is discarded in the previous pop front, the
        index difference between x and i' is strictly better than x and i + 2
        for i' < i + 2
     2. x is discarded during some previous pop back:
        contradiction: as P[some previous mq.back()] <= x, 
        if P[some previous mq.back()] is in mq[i+1], then this is a 
        strictly batter solution. otherwise 
        mq[i+1].back() <= P[some previous mq.back()] is also a strictly better
        solution.
    */
public:
    int shortestSubarray(vector<int>& A, int K) {
        deque<int> mq;
        vector<int> P {0};
        for (int i = 0; i < A.size(); ++i) {
            P.push_back(A[i] + P.back());
        }
        int ans = P.size() + 1;
        for (int i = 0; i < P.size(); ++i) {
            while (mq.size() && P[i] - P[mq.front()] >= K) {
                ans = min(ans, i - mq.front());
                mq.pop_front();
            }
            while (mq.size() && P[i] <= P[mq.back()]) {
                mq.pop_back();
            }
            mq.push_back(i);
        }
        
        return ans == P.size() + 1 ? -1 : ans;
    }
};
