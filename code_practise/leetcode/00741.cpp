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

Suboptimial structure:
Because the round trip are two path going down and right (law of symmetry)
if we draw an anti-diag, it must touch each of the path exaclty once.
***********************************************************************************
* Therefore, for each anti-diag, we specify the position of the two interactions, *
* then we uniquely identify a whole round trip.                                   *
***********************************************************************************

The recursive structure looks like this: to solve point P, Q at the longer
diag, we reduce it to the pairs on the previous diag, with the following
4 subproblems:
(P up, Q up)
(P up, Q left)
(P left, Q up)
(P left, Q left)
if none of them can construct a valid P Q pair (all four points are not reachable),
then pair P Q is considered not reachable. Use -1 to mark not reachable.
Of course if P or Q is -1, the pair is also not reachable.
 +--------------------------------------------------/-----------------                   
 |                                                /-               -/|                   
 |                                        P up  /-               -/  |                   
 |                                            /|               -/    |                   
 |                                          /- |             -/      |                   
 |                                        /-   |           -/        |                   
 |                                      /-     |         -/          |                   
 |                                    /-       |       -/            |                   
 |                                  /-         |     -/              |                   
 |                                /-           |   -/                |                   
 |                      P left  /-             | -/                  |                   
 |                            -----------------|/                    |                   
 |                          /-               -/ P                    |                   
 |                   Q up /-               -/                        |                   
 |                      /|               -/                          |                   
 |                    /- |             -/                            |                   
 |                  /-   |           -/                              |                   
 |                /-     |         -/                                |                   
 |              /-       |       -/                                  |                   
 |            /-         |     -/                                    |                   
 |          /-           |   -/                                      |                   
 |        /-             | -/                                        |                   
  Q left/----------------|/                                          |                   
 |    /-               -/ Q                                          |                   
 |  /-               -/                                              |                   
 |/-               -/                                                |                   
 -               -/                                                  |                   
 |             -/                                                    |                   
 |           -/                                                      |                   
 |         -/                                                        |                   
 |       -/                                                          |                   
 |     -/                                                            |                   
 |   -/                                                              |                   
 | -/                                                                |                   
 -/------------------------------------------------------------------+  
 
 Implementation considerations:
 P and Q are uniquely identified by their x coordinate given the diag.
 When diag is on the lower part of the matrix, we must do a coordinate transformation
 to get the correct grid[P_x][P_y] and grid[Q_x][Q_y].
 Also, note the nature symmetricity bettween the solution dp[l][P][Q] and dp[l][Q][P].
