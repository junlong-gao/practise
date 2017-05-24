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
	public:
		vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
			if(root == nullptr) return {};
			deque<TreeNode*> q;
			q.push_back(root);
			bool alter = false;
			vector<vector<int>> rst;
			while(!q.empty()){
				int n = q.size();
				rst.push_back({});
				while(n--){
					auto top = q.front();
					rst.back().push_back(top->val);
					q.pop_front();
					if(top->left) q.push_back(top->left);
					if(top->right) q.push_back(top->right);
				}
				if(alter){
					reverse(rst.back().begin(), rst.back().end());
				}
				alter = !alter;

			}
			return rst;
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


