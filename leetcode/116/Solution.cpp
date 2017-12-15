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
    struct TreeLinkNode {
      int val;
      TreeLinkNode *left, *right, *next;
      TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
    };
	class Solution {
		void search(TreeLinkNode* root){
			if(root== nullptr){
				return;
			}
			if(root->left != nullptr){
				TreeLinkNode* l, *r;
				l = root->left, r = root->right;
				while(l&&r){
					l->next = r;
					l = l->right;
					r = r->left;
				}
				search(root->left);
				search(root->right);
			}
		}
	public:
		void connect(TreeLinkNode *root) {
            search(root);
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            TreeLinkNode root(0), l(1), r(2), ll(3), lr(4), rl(5), rr(6);
            root.left = &l; root.right = &r;
			l.left = &ll, l.right = &lr, r.left = &rl, r.right = &rr;
			testObj.connect(&root);
			REQUIRE(root.next == NULL);
			REQUIRE(l.next == &r);
			REQUIRE((ll.next == &lr)); REQUIRE(lr.next == &rl); REQUIRE(rl.next == &rr);
		}
	}
}


