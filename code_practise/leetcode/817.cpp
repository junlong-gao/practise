/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };

while true
        while node != null and node->val is not in G
                node = node.next
        if node == null break
        comp++;
        while node != null and node->val is in G
node = node.next
 */
class Solution {
 public:
  int numComponents(ListNode* head, vector<int>& G) {
    int comp = 0;
    unordered_set<int> gg;
    for (auto v : G) {
      assert(gg.count(v) == 0);
      gg.insert(v);
    }

    while (true) {
      while (head != nullptr && gg.count(head->val) == 0) {
        head = head->next;
      }
      if (head == nullptr) break;
      comp++;
      while (head != nullptr && gg.count(head->val) == 1) {
        head = head->next;
      }
    }
    return comp;
  }
};
