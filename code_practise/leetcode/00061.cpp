class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode* walker = head;
        int n = 0;
        while(walker) {
          walker = walker->next;
          n++;
        }
        if (n <= 1) return head;
        k = k % n; // if n is too small, this is division by 0
        if (k == 0) return head;
        int countDown = n - k - 1;
        ListNode *tail = head, *cutPoint = head;
        walker = head;
        while (walker) {
          if(countDown-- > 0) {
            cutPoint = cutPoint->next;
          }
          tail = walker;
          walker = walker->next;
        }
        ListNode *rest = cutPoint->next;
        cutPoint->next = nullptr;
        assert(rest);
        tail->next = head;
        return rest;
    }
};