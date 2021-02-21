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
        int n1 = 0; int n2 = 0;
        ListNode *tmp = l1;
        while (tmp) {
            n1++; tmp = tmp->next;
        }
        tmp = l2;
        while (tmp) {
            n2++; tmp = tmp->next;
        }

        ListNode *res = nullptr;
        while (n1 > 0 || n2 > 0) {
            ListNode *next = new ListNode;
            if (n1 > n2) {
                next->val = l1->val;
                n1--; l1 = l1->next;
            } else if (n1 < n2) {
                next->val = l2->val;
                n2--; l2 = l2->next;
            } else {
                next->val = l1->val + l2->val;
                n1--; l1 = l1->next;
                n2--; l2 = l2->next;
            }
            if (res == nullptr) {
                res = next;
            } else {
                next->next = res;
                res = next;
            }
        }

        if (res == nullptr) {
            return res;
        }

        ListNode *head = nullptr;
        int carry = 0;
        while (res) {
            res->val += carry;
            carry = res->val / 10;
            res->val = res->val % 10;

            ListNode *next = new ListNode(res->val);
            if (head == nullptr) {
                head = next;
            } else {
                next->next = head;
                head = next;
            }

            res = res->next;
        }


        if (carry) {
            ListNode *next = new ListNode(carry);
            next->next = head;
            head = next;
        }
        return head;
    }
};