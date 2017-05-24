#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/* very cute dp:
 * idea: the current solution gives the "min" solution of the
 * recursive state. This is highly non-trivial and gives a
 * cute example where max problem is solved by minimize
 * recursive solutions
 */

class Solution{
public:
    int maxmialSquare(vector<vector<char>>& matrix){
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m));
        int cur_max = 0;
        for(int i = 0; i < n; ++i){
            dp[i][0] = matrix[i][0] - '0';
            if(dp[i][0] > cur_max) cur_max = dp[i][0];
        }
        for(int j = 0; j < n; ++j){
            dp[0][j] = matrix[0][j] - '0';
            if(dp[0][j] > cur_max) cur_max = dp[0][j];
        }
        for(int i = 1; i < n; ++i){
            for(int j = 1; j < m; ++j){
                if(matrix[i][j] - '0' == 0) dp[i][j] = 0;
                else{
                    int t1 = dp[i-1][j];
                    int t2 = dp[i][j-1];
                    int t3 = dp[i-1][j-1];
                    dp[i][j] = min(t1, min(t2,t3)) + 1;
                }
                if(dp[i][j] > cur_max) cur_max = dp[i][j];
            }
        }
        return cur_max * cur_max;
    }
};

int main(){
    vector<vector<char>> matrix(5, vector<char>(5, '0'));
    matrix[0][0] = matrix[0][2] = matrix[0][4] = '1';
    matrix[1][0] = matrix[2][0] = matrix[3][0] = '1';
    matrix[2][2] = matrix[1][2] = matrix[2][1] = '1';
    matrix[1][1] = matrix[4][2] = matrix[3][1] = '1';
    matrix[3][2] = '1';
    Solution s;
    cout << s.maxmialSquare(matrix);

    return 0;
}
