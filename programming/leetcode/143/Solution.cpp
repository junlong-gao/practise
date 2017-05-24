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
        void reorderList(ListNode* head) {
            if(head==nullptr) return;
            ListNode* fast = head, *slow=head, *tmp = nullptr;
            while(fast && fast->next){
                fast = fast->next;
                if(fast){
                    fast = fast->next;
                    tmp = slow;
                    slow = slow->next;
                }
            }
            ListNode* mid = slow;
            if(fast){
                mid = mid->next;
                slow->next = nullptr;
            }else{
                tmp->next = nullptr;
            }
            ListNode* prev = nullptr, *walker = mid;
            while(walker){
                ListNode* next = walker->next;
                walker->next = prev;
                prev = walker;
                walker = next;
            }
            walker = head;
            while(walker && prev){
                ListNode* next = walker->next;
                walker->next = prev;
                ListNode* prev_next = prev->next;
                prev->next = next;
                walker = next;
                prev = prev_next;
            }
            
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){

		}
	}
}


