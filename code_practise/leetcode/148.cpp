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
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        // floyd link cycle detection
        ListNode *f = head->next, *s = head, *d;
        while (f && f->next) {
            s = s->next;
            f = f->next; f = f->next;
        }
        
        ListNode *n1 = head, *n2 = s->next;
        s->next = nullptr;
        
        n1 = sortList(n1);
        n2 = sortList(n2);

        ListNode dummy(0), *ret = &dummy;
        while (n1 && n2) {
            if (n1->val > n2->val) {
                ret->next = n2;
                n2 = n2->next;
            } else {
                ret->next = n1;
                n1 = n1->next;
            }
            ret = ret->next;
        }
        if (n2 == nullptr) {
            ret->next = n1;
        } else {
            ret->next = n2;
        }

        return dummy.next;
    }
};
