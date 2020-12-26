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
      ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
         int carry = 0;
         ListNode ret(0);
         ListNode* walker = &ret;
         while(l1 && l2){
            int val = (l1->val + l2->val + carry) % 10;
            carry = (l1->val + l2->val + carry) / 10;
            walker->next = new ListNode(val);
            walker = walker->next; l1 = l1->next; l2=l2->next;
         }
         while(l1){
            int val = (l1->val + carry) % 10;
            carry = (l1->val + carry) / 10;
            walker->next = new ListNode(val);
            walker = walker->next; l1 = l1->next;
         }
         while(l2){
            int val = (l2->val + carry) % 10;
            carry = (l2->val + carry) / 10;
            walker->next = new ListNode(val);
            walker = walker->next; l2 = l2->next;
         }
         if(carry){
            walker->next = new ListNode(carry);
         }
         return ret.next;
      }
   };

   TEST_CASE("tests"){
      Solution testObj;
      SECTION("sample"){

      }
   }
}


