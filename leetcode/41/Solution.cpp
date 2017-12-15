#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
    class Solution {
    public:
        int firstMissingPositive(vector<int>& nums) {
            for(int i = 0; i < nums.size(); ++i){
                while(nums[i] > 0 && nums[i] <= nums.size() && nums[nums[i]-1]!=nums[i]){
                    cout << nums[i] << " " << nums[nums[i]-1]<<endl;
                    swap(nums[i], nums[nums[i]-1]);
                }
            }
            for(int i = 0; i < nums.size(); ++i){
                if(nums[i] != i+1) return i+1;
            }
            return nums.size()+1;
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            
		}
	}
}


