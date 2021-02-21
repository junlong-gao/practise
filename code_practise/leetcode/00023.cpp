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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](const ListNode *l, const ListNode *r) {
            return l->val > r->val;
        };
        priority_queue<ListNode *, vector<ListNode*>, decltype(cmp)> pq(cmp);
        
        for (auto l : lists) {
            if (l) {
                pq.push(l);
            }
        }
        
        ListNode dummy;
        ListNode *cur = &dummy;
        while (pq.size()) {
            auto top = pq.top();
            pq.pop();
            cur->next = top;
            cur = cur->next;
            
            top = top->next;
            if (top) {
                pq.push(top);
            }
        }
        
        return dummy.next;
    }
};
