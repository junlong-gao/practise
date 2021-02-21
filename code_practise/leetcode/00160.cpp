/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int n1 = 0, n2 = 0;
        ListNode *h1 = headA, *h2 = headB;
        while (h1 || h2) {
            if (h1) {
                n1++; h1 = h1->next;
            }
            if (h2) {
                n2++; h2 = h2->next;
            }
        }
        
        h1 = headA; h2 = headB;
        while (h1 != h2) {
            if (n2 > n1) {
                h2 = h2->next;
                n2--;
            } else if (n1 > n2) {
                h1 = h1->next;
                n1--;
            } else {
                h1 = h1->next; h2 = h2->next;
                n1--; n2--;
            }
        }
        
        return h1;
    }
};