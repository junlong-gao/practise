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
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    class Solution {
        double abs(double x){
            return x > 0 ? x : -x;
        }
        int f(int x, int a, int b, int c){
            return a*x*x + b * x + c;
        }
    public:
        vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
            if(a == 0){
                for(int i = 0; i < nums.size(); ++i){
                    nums[i] = f(nums[i], a,b,c);
                }
                if(b < 0){
                    reverse(nums.begin(), nums.end());
                }
                return nums;
            }
            double center = - (double)(b)/(double)(2*a);
            int i = 0, j = nums.size() - 1;
            vector<int> ret;
            while(i <= j){
                if(this->abs(nums[i] - center) > this->abs(nums[j] - center)){
                    ret.push_back(f(nums[i++], a, b, c));
                }else{
                    ret.push_back(f(nums[j--],a,b,c));
                }
            }
            if(a > 0) reverse(ret.begin(), ret.end());


            return ret;
        }
    };



	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


