
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
		k = nums.size() - k;
        int low = 0, high = nums.size()-1, i, j;
        while (low <= high) {
			i = low; j = high + 1;
            while (1) {
                while(i<high&&nums[++i]<nums[low]);
                while (j>low&&nums[low]<nums[--j]);
                if (i>=j) break;
                swap(nums, i, j);
            }
            swap(nums, j, low);
			if (j<k) {
				low = j + 1;
			}else if(j>k){
				high = j - 1;
			}else{
				break;
			}
        }
		return nums[j];
    }
    void swap(vector<int>& nums,int i,int j){
        int tmp = nums[i];
        nums[i]=nums[j];
        nums[j]=tmp;
    }
};

int main(int argc, const char * argv[]) {
	vector<int> test = {3,2,1};
	
	Solution mysolutions;
	mysolutions.findKthLargest(test, 2);
	
    return 0;
}
