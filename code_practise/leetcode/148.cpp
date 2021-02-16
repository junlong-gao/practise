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
    ListNode *partition(ListNode *h, ListNode *e) {
        { // otherwise TLE...
            ListNode *cur = h; int n = 0;
            while (cur != e) {
                n++; cur = cur->next;
            }
            int pLoc = rand() % n;
            cur = h;
            while (pLoc-->0) {
                cur = cur->next;
            }
            swap(cur->val, h->val);
        }
        ListNode *pivit = h;
        ListNode *i = h, *j = h->next;
        // [h, i] (i, j) [j, e)
        while (j != e) {
            if (j->val <= h->val) {
                i = i->next;
                swap(j->val, i->val);
            }
            j = j->next;
        }
        swap(h->val, i->val);
        return i;
    }

    void qsort(ListNode *h, ListNode *e) {
        if (h == e || h->next == e) {
            return;
        }

        ListNode *mid = partition(h, e);
        qsort(h, mid);
        qsort(mid->next, e);
    }
public:
    ListNode* sortList(ListNode* head) {
        qsort(head, nullptr);
        return head;
    }
};
