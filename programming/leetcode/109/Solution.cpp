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
		TreeNode* builder(vector<int>& vals, int start, int end){
			if(start >= end) return nullptr;
			int mid = start + (end-start)/2;
			TreeNode* root = new TreeNode(vals[mid]);
			//cout << root->val << endl;
			root->left = builder(vals, start, mid);
			root->right = builder(vals, mid+1, end);
			return root;
		}
	public:
		TreeNode* sortedListToBST(ListNode* head) {
			vector<int> vals;
			while(head){
				vals.push_back(head->val);
				head = head->next;
			}
			return builder(vals, 0, vals.size());
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


