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
		bool search(deque<TreeNode*>& rst, TreeNode* root, TreeNode* target){
			if(root == nullptr) return false;
			if(root == target || search(rst, root->left, target) || search(rst, root->right, target)){
				rst.push_front(root);
				return true;
			}
			return false;
		}
	public:
		TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
			if(root == NULL) return root;
			deque<TreeNode*> left_path;
			deque<TreeNode*> right_path;
			assert(search(left_path, root, p));
			assert(search(right_path, root, q));
			TreeNode* ret = NULL;
			while(!left_path.empty() && !right_path.empty() && left_path.front() == right_path.front()){
				ret = left_path.front();
				left_path.pop_front();
				right_path.pop_front();
			}
			return ret;
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
			TreeNode root(0);
			TreeNode l(1);
			TreeNode r(2);
			root.left = &l;
			root.right = &r;
			auto rst = testObj.lowestCommonAncestor(&root, &root, &r);
			REQUIRE(rst == &root);

		}
	}
}


