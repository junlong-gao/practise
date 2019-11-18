/*
Using prefix sum, this is essentially the following problem: Let A be an
array of int, and let K be a non-negative int. Define opt(j) to be the
largest index i <= j such that A[j] - A[i] >= K, for all j in index range [0,
len(A) - 1]. Find min_{0 <= j < len(A)} opt(j).

Assume we already know how to solve for problem arr[0...n], adding element
arr[n + 1]. Naively, we can construct a "candidate set" for arr[n + 1]:
set[n + 1], in which we can examine diff arr[n+1] - e for e in set[n+1].
This, however, will take too much time in the inductive step if we naively
use arr[0...n] as set[n + 1].

From induction, we know we will have such set for arr[n]: set[n]. The
question becomes how to compute set[n+1] from set[n], perhaps discarding some
elements in set[n] to obtain set[n+1] in order to efficiently update opt via
arr[n+1].
Of course, arr[n] will join set[n] to form set[n+1]. To consider which
elements we can discard from set[n] in order to get set[n+1], we first see
for any e in set[n], if e >= arr[n], e is useless for arr[n + 1] because
   1. if arr[n + 1] - e >= K, then arr[n] is a better solution 
   2. else, then e is not a valid candidate and not considered for computing
      a solution arr[n + 1]
This hints the sorted nature of set[n]: when adding arr[n], we always remove
elements >= arr[n], so it is not decreasing. Second, if arr[n] - e >= K, then
e is not worth keeping when adding arr[n + 1] because 
   1. if arr[n + 1] - e >= K, then arr[n] is a shorter solution, 
   2. else it is not a valid candiate and not used at all for computing
      a solution arr[n + 1].

Now by inductive hypothesis, we know we can compute the candidate set for all
arr[n + 1] and use it to compute opt(n + 1) and update the best opt(j) seen
so far. This is much more efficient than computing arr[n+1] from nothing.
This both gives an efficient algorithm and proof (correct by construct).

Curiously, if we would like to find opt(n) for all n, we cannot apply the
second optimization in the inductive step. This eventually gives a O(nlogn)
solution using binary search in the queue.
*/

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        deque<int> mq;
        vector<int> P {0};
        for (int i = 0; i < A.size(); ++i) {
            P.push_back(A[i] + P.back());
        }
        int ans = P.size() + 1;
        for (int i = 0; i < P.size(); ++i) {
            /*
            Inv: mq is the candidate set for P[i]
            */

            // Use the candidate set to update ans
            while (mq.size() && P[i] - P[mq.front()] >= K) {
                ans = min(ans, i - mq.front());
                mq.pop_front();
            }

            // Construct candidate set for P[i + 1], essentially,
            // the only new candidate is P[i], and we can remove a
            // few.
            while (mq.size() && P[i] <= P[mq.back()]) {
                mq.pop_back();
            }
            mq.push_back(i);
        }
        
        return ans == P.size() + 1 ? -1 : ans;
    }
};
