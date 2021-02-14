define CATCH_CONFIG_MAIN
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
	public:

	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
class Solution {
    /*
    map location -> index
    */
public:
    bool canCross(vector<int>& stones) {
        unordered_map<int, int> pToIdx;
        for (int i = 0; i < stones.size(); ++i) {
            pToIdx[stones[i]] = i;
        }
        
        unordered_map<int, set<int>> fesiables; // idx -> posible jump
        fesiables[0].insert(0);
        for (int i = 0; i < stones.size(); ++i) {
            int loc = stones[i];
            for (auto jump : fesiables[i]) {
                for (auto newJump : {jump - 1, jump, jump + 1}) {
                    if (newJump > 0 && pToIdx.count(loc + newJump)) {
                        fesiables[pToIdx[loc + newJump]].insert(newJump);
                    }
                }
            }
        }
        
        return fesiables[stones.size() - 1].size() > 0;
    }
};}


