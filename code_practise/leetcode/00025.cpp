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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy; dummy.next = head;
        ListNode *prevGroupLast = &dummy;
        while (prevGroupLast != nullptr) {
            ListNode *newGroupFirst = prevGroupLast->next;
            
            ListNode *last = prevGroupLast;
            for (int i = 0; i < k; ++i) {
                last = last->next;
                if (last == nullptr) {
                    return dummy.next;
                }
            }
            
            ListNode *nextFirst = last->next;
            ListNode *probe = newGroupFirst, *prev = prevGroupLast;
            for (int i = 0; i < k; ++i) {
                ListNode *tmp = probe->next;
                probe->next = prev;
                prev = probe;
                probe = tmp;
            }
            
            prevGroupLast->next = last;
            newGroupFirst->next = nextFirst;
            prevGroupLast = newGroupFirst;
        }
        
        return dummy.next;
    }