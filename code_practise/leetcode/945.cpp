/*
Assume we know how to find the min increase for array[0...n], consider appending
a new n + 1 th element v. Let v' be the max for array[0...n] and let T be the
max after the min increase in array[0...n].

if v > T, then the min increase for array[0...n + 1] the same as array[0...n]
else if v == T, the min increase must be min increase of array[0...n] + 1,
else, we know v < T, so there are elements in (v, T] as a result of increase for
array[0...n]. We know that (v, T] cannot have a hole, as otherwise a strictly
better solution can be obtained for array[0...n], so the min increase for making
array[0...n + 1] unique is to add v to T + 1.

The following code uses the inductive proof and maintain T at A[i - 1].
*/
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        sort(A.begin(), A.end());
        int ret = 0;
        for (int i = 1; i < A.size(); ++i) {
            if (A[i] <= A[i - 1]) {
                ret += 1 + A[i - 1] - A[i];
                A[i] = A[i - 1] + 1;
            }
        }
        
        return ret;
    }
};
