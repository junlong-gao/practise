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
        int numTrees(int n) {
            vector<int> bs(n + 1, 0);
            if(n < 2) return 1;
            bs[0] = bs[1] = 1;
            for(int i = 2; i <= n; ++i){
                for(int k = 0; k < i; ++k){
                    bs[i] += bs[k] * bs[i-k-1];
                }
            }
            return bs[n];
        }
    };
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            REQUIRE(testObj.numTrees(3) == 5);
		}
	}
}


