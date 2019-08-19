/*
 In order to consider the longest montain, the next candidate can start at least where the current
 one finishes.
 */
class Solution {
public:
    int longestMountain(vector<int>& A) {
        int n = A.size();
        int s = 0; int ans = 0;
        while (s < n) {
            int e = s;
            while (e + 1 < n && A[e] < A[e + 1]) {
                e++;
            }
            
            if (e == s) {
                s = e + 1;
                continue;
            }
            
            int p = e;
            while (e + 1 < n && A[e] > A[e + 1]) {
                e++;
            }
            if (e == p) {
                s = e + 1;
                continue;
            }
            
            ans = max(ans, e - s + 1);
            s = e;
        }
        return ans;
    }
};
