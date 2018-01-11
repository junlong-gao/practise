class Solution {
public:
    int cherryPickup(vector<vector<int>> grid) {
       int n = grid.size();
       
       int dp[2*n][n][n];
       
       for(int ll = 1; ll <= 2*n - 1; ++ll) {
         int l = ll;
         if (ll > n) {
           l = 2*n - l;
         }
         
         for(int dpx = 0; dpx < l; ++dpx) {
           for (int dqx = dpx; dqx < l; ++dqx) {
             int px = dpx, qx = dqx;

             int py = l - 1 - px;
             int qy = l - 1 - qx;
             
             // we are in the lower triangle, do a coordinate transform.
             if (ll > n) {
               px = n - px - 1;
               qx = n - qx - 1;
               py = n - py - 1;
               qy = n - qy - 1;
             }
             
             if (ll == 1) {
               // origin
               dp[ll][px][qx] = grid[px][py];
               continue;
             }
             
             // impossible pair to appear on path.
             if (grid[px][py] < 0 || grid[qx][qy] < 0) {
               dp[ll][px][qx] = dp[ll][qx][px] = -1;
               continue;
             }
             
             int base = (qx > 0 && px > 0? dp[ll-1][px - 1][qx - 1] : -1); // p up q up
             base = max(base, ((qx > 0 && py > 0) ? dp[ll-1][px][qx - 1] : -1)); // p left q up

             base = max(base, ((px > 0 && qy > 0) ? dp[ll-1][px - 1][qx] : -1)); // p up q left

             base = max(base, ((py > 0 && qy > 0) ? dp[ll-1][px][qx] : -1)); // p left q left

             if (base < 0) {
               // none of the four source can reach state p q
                dp[ll][px][qx] = dp[ll][qx][px] = -1;
               continue;
             }
             
             dp[ll][px][qx] = base + grid[px][py] + (px == qx? 0 : grid[qx][qy]);
             dp[ll][qx][px] = dp[ll][px][qx];
           }
         }
       }
       
       return max(dp[2*n - 1][n - 1][n - 1], 0);
    }
};

/*
[[0,1,-1],[1,0,-1],[1,1,1]]
[[0,0,0],[1,0,-1],[1,1,1]]
[[1,1,1,0,0],[0,0,1,0,1],[0,0,1,0,0],[1,0,1,0,0],[0,0,1,1,1]]
5
4
10
*/
