class Solution {
  /*
  reverse in range [l...r)
  */
  ListNode *reverse(ListNode *l, ListNode *r) {
    ListNode *prev = r;
    while (l != r) {
      auto t = l->next;
      l->next = prev;
      prev = l;
      l = t;
    }
    return prev;
  }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
      if (k <= 1) return head;
      ListNode dummy(0);
      dummy.next = head;
      ListNode *cur = &dummy;
      
      while (cur && cur->next) {
        ListNode *tail = cur->next;
        int count = k;
        while (count > 0 && tail) {
          tail = tail->next;
          count--;
        }
        if (count) break;

        auto t = cur->next;
        cur->next = reverse(cur->next, tail);
        cur = t;
      }
      return dummy.next;
    }
};
