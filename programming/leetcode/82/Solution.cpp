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
        ListNode* deleteDuplicates(ListNode* head) {
            ListNode* walker = head, *prev = nullptr;
            if(head == nullptr) return nullptr;
            ListNode tmp(head->val - 1);
            prev = &tmp;
            tmp.next = head;
            while(walker){
                ListNode* probe = walker->next;
                while(probe && probe->val == walker->val){
                    ListNode* next = probe->next;
                    //delete probe;
                    probe = next;
                }
                //delete walker
                if(probe != walker->next){
                    prev->next = probe;
                    walker = probe;
                }else{
                    prev = walker;
                    walker = walker->next;
                }
            }
            return tmp.next;
        }
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


