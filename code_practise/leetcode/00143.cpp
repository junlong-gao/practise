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
    void reorderList(ListNode* head) {
        if (head == nullptr) { return; }
        int n = 0;

        {
            ListNode *cur = head;
            while (cur) {
                n++; cur = cur->next;
            }
        }

        int mid = (n - 1) / 2; ListNode *midNode = head;
        while (mid-->0) {
            midNode = midNode->next;
        }

        ListNode *prev = nullptr;
        {
            ListNode *cur = midNode->next;
            midNode->next = nullptr;
            while (cur) {
                ListNode *tmp = cur->next;
                cur->next = prev;
                prev = cur;
                cur = tmp;
            }
        }

        ListNode *firstHalf = head, *secondHalf = prev;
        while (firstHalf && secondHalf) {
            ListNode *tmp1 = firstHalf->next, *tmp2 = secondHalf->next;
            firstHalf->next = secondHalf;
            secondHalf->next = tmp1;
            firstHalf = tmp1;
            secondHalf = tmp2;
        }
    }
};