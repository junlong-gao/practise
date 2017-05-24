#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <deque>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"

using namespace std;
class Solution {
    vector<vector<int>> dp;
    int n;
    const int INF = 100000000;
    int search(int i, int j, vector<vector<int>>& triangle){
        if(i<0 || i >= n || j > i || j < 0) return INF;
        if(i==n-1) return triangle[i][j];
        if(dp[i][j] != -1) return dp[i][j];
        int& ans = dp[i][j];
        ans = triangle[i][j] + min(search(i+1,j,triangle), search(i+1, j+1, triangle));
        return ans;
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        cerr << "test" << endl;
        for(auto& ele: triangle){
            for(auto& num:ele){
                cerr << num <<" ";
            }
            cerr << endl;
        }
        dp.resize(triangle.size());
        for(auto& ele:dp){
            ele.resize(triangle.size(), -1);
        }
        n = triangle.size();
        return search(0,0,triangle);
    }
};

int main(){
    std::ifstream in(FILENAME);
    if(DEBUG){
        std::cin.rdbuf(in.rdbuf());
    }
    vector<vector<int>> triangle = {{1},{2,3},{4,5,6},{7,8,9,10}};
    Solution s; 
    cout << s.minimumTotal(triangle) << endl;

    return 0;
}
