#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
	class Solution {
	public:
		void nextPermutation(vector<int>& nums) {
			int i = nums.size() - 1;
			int cur_max = numeric_limits<int>::min();
			while(i>=0){
				if(nums[i] < cur_max) break;
				cur_max = max(cur_max, nums[i--]);
			}

			if(i < 0) {
				sort(nums.begin(), nums.end());
				return;
			}

			int j = i+1;
			int cur_min = numeric_limits<int>::max();
			int idx = i;
			while( j < nums.size()){
				if(nums[j] > nums[i]){
					if(nums[j] < cur_min){
						cur_min = nums[j];
						idx = j;
					}
				}
				++j;
			}
			swap(nums[i], nums[idx]);
			sort(nums.begin() + i + 1, nums.end());
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
		}
	}
}


