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
        vector<int> maxNumber(vector<int>& nums1, int k){
            vector<int> rst;
            int j = 0, l = k;
            while(rst.size() < l){
                int cur = -1;
                int idx = -1;
                for(int i = j; i < nums1.size() - k + 1; ++i){
                    if(nums1[i] > cur){
                        cur = nums1[i];
                        idx = i;
                    }
                }
                rst.push_back(cur);
                j = idx + 1;
                k--;
            }
            return rst;
        }
        bool less(vector<int>& nums1, int i, vector<int>& nums2, int j){
            while(i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]){
                ++i, ++j;
            }
            if(i == nums1.size()) return true;
            if(j == nums2.size()) return false;
            return nums1[i] < nums2[j];
        }
        vector<int> merge(vector<int>& nums1, vector<int>& nums2){
            vector<int> rst;
            int i = 0, j = 0;
            while(i < nums1.size() && j < nums2.size()){
                if(less(nums1, i, nums2, j)) rst.push_back(nums2[j++]);
                else rst.push_back(nums1[i++]);
            }
            while(i < nums1.size()){
                rst.push_back(nums1[i++]);
            }
            while(j < nums2.size()){
                rst.push_back(nums2[j++]);
            }
            return rst;
        }
    public:
        vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
            vector<int> rst;
            for(int i = max(0, (int)(k - nums2.size())); i <= min((int)(nums1.size()), k); ++i){
                auto lhs = maxNumber(nums1, i);
                auto rhs = maxNumber(nums2, k - i);
                auto cur = merge(lhs, rhs);
                if(less(rst, 0, cur, 0)){
                    rst = cur;
                }
            }
            return rst;
        }
        
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            vector<int> nums1 = {3,9};
            vector<int> nums2 = {8,9};
            auto rst = testObj.maxNumber(nums1, nums2, 3);
            vector<int> expected = {9,8,9};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
        SECTION("sample2"){
            vector<int> nums1 = {3, 4, 6, 5};
            vector<int> nums2 = {9, 1, 2, 5, 8, 3};
            auto rst = testObj.maxNumber(nums1, nums2, 5);
            vector<int> expected = {9, 8, 6, 5, 3};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
        }
        SECTION("sample2"){
            vector<int> nums1 = {6,7};
            vector<int> nums2 = {6,0,4};
            auto rst = testObj.maxNumber(nums1, nums2, 5);
            vector<int> expected = {6,7,6,0,4};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
        }
	}
}


