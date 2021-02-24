/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode dummy;
        ListNode *head = &dummy;
        
        while (carry || l1 || l2) {
            int v = carry;
            if (l1) {
                v += l1->val; l1 = l1->next;
            }
            if (l2) {
                v += l2->val; l2 = l2->next;
            }
            head->next = new ListNode(v%10);
            carry = v / 10;
            head = head->next;
        }
        
        return dummy.next;
    }
};