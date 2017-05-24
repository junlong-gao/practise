#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        vector<int> rst(nums);
        sort(rst.begin(), rst.end());
        int i;
        for(i = 0; 2*i + 1 < nums.size(); ++i){
            nums[2*i + 1] = rst[nums.size() - 1 - i];
        }
        for(int j = i; j < nums.size(); ++j){
            nums[2*(j-i)] = rst[nums.size() - 1 - j];
        }
    }
};

int main(){
    Solution s;
    vector<int> a = {1,5,1,1,6,4};
    s.wiggleSort(a);
    for(auto x : a){
        cout << x << " ";
    }
}
