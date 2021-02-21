/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
/*
Waven trick: meld 2 lists into 1 list (even, odd, even, odd ...)
and set the random for odd nodes.
Un-waven it, consider the last node case.
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;
        Node *cur = head;
        while (cur) {
            Node *oldNext = cur->next;
            cur->next = new Node(cur->val);
            cur->next->next = oldNext;
            cur = oldNext;
        }
        
        cur = head;
        while (cur) {
            cur->next->random = cur->random;
            if (cur->next->random) {
                cur->next->random = cur->next->random->next;
            }
            cur = cur->next->next;
        }
        
        cur = head;
        Node *ret = cur->next;
        while (cur) {
            Node *oldNext = cur->next->next;
            if (oldNext == nullptr) {
                cur->next->next = nullptr;
            } else {
                cur->next->next = oldNext->next;
            }
            
            cur->next = oldNext;
            cur = cur->next;
        }
        return ret;
    }
};
