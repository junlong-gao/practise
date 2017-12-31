#include <iostream>
#include <vector>

using namespace std;

class Solution{
public:
    int rob(vector<int>& nums){
        vector<int> dp(nums.size());
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return nums.front();
        dp[0] = nums[0];
        cout << dp[0] << endl;
        dp[1] = max(nums[1], nums[0]);
        cout << dp[1] << endl;
        for(int i = 2; i < (int)nums.size(); i++){
            dp[i] = max(nums[i] + dp[i-2], dp[i - 1]);
            cout << dp[i] << endl;
        }
        return dp.back();
    }
};


int main(){
    vector<int> test = {1,0,2,3,1,4,1};
    Solution s;
    cout <<s.rob(test)<< endl;
    return 0;
}
