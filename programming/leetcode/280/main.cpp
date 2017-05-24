#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;




class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        for(int i = 1; i < nums.size(); ++i){
            if((i%2) == (nums[i-1]>nums[i])){
                swap(nums[i-1],nums[i]);
            }
        }
    }
};

int main(){
    vector<int> tmp = {3,5,2,1,6,4};
    Solution mysolution;
    mysolution.wiggleSort(tmp);
    for(int i = 0; i < (int)tmp.size(); i ++){
        cout << tmp[i] <<" ";
    }
	return 0;	
}
