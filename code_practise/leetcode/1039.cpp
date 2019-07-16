class Solution {
    vector<vector<int>> dp;
    int solve(vector<int>& A, int i, int j) {
        if (dp[i][j] != -1) return dp[i][j];
        
        int &ans = dp[i][j];
        if (j == i + 2) {
            return ans = A[i] * A[i+1] * A[j];
        }
        
        if (j == i + 1) {
            return ans = 0;
        }
        
        ans = INT_MAX;
        for (int k = i + 1; k < j; ++k) {
            ans = min(ans, A[i] * A[j] * A[k] + solve(A, i, k) + solve(A, k, j));
        }
        
        return ans;
    }
public:
    int minScoreTriangulation(vector<int>& A) {
        dp.resize(A.size(), vector<int>(A.size(), -1));
        return solve(A, 0, A.size() - 1);
    }
};

/*
One way to look at the suboptimal structure is to think as removing one vertex
at a time.  But this soon leads to exponential space: 2 ^ (n - 3) of possible
branches to explore.

Another way to model the triangulation is to think that for every edge, it will
eventually have a third vertex associated with it for triangulation. Start with
any edge, and pick the vertex associated with it, then it becomes 2 separate
problems of the same form, but smaller size.  This modeling is better than the
first one as the space to explore is considerably smaller: every time we care
problems of a contiguous range of vertices.

Why this modeling reduces the number of states to explore? The number of
triangulation for a given convex polygon is not too large to begin with. For
any edge e given and fixed, all the triangulation with e associated with vertex
k is disjoint with e associated with vertex k’, if k != k’. Since edge can be
used exactly once. This is clearly not the case for classifying using which
vertex to be replaced by an edge.  (Note it is instructive to compute the total
number of triangulations)
*/

