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
    public:
        void connect(TreeLinkNode *root) {
            if(root == NULL) return;
            deque<TreeLinkNode*> q;
            q.push_back(root);
            while(!q.empty()){
                int size = q.size();
                for(int i = 0; i < size; ++i){
                    auto front = q.front();
                    q.pop_front();
                    if(i == size - 1){
                        front->next = NULL;
                    }else{
                        front->next = q.front();
                    }
                    if(front->left){
                        q.push_back(front->left);
                    }
                    if(front->right){
                        q.push_back(front->right);
                    }
                }
            }
        }
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            TreeLinkNode root(1);
            TreeLinkNode l(2);
            TreeLinkNode r(3);
            TreeLinkNode ll(4);
            TreeLinkNode lr(5);
            TreeLinkNode rr(7);
            root.left = &l; root.right = &r;
            l.left = &ll; l.right = &lr;
            r.right = &rr;
            testObj.connect(&root);
            REQUIRE(root.next == NULL);
            REQUIRE(l.next == &r); REQUIRE(r.next == NULL);
            REQUIRE(ll.next == &lr); REQUIRE(lr.next == &rr); REQUIRE(rr.next == NULL);


		}
	}
}


