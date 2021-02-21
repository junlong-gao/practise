/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node *w = head;
        if (w == nullptr) {
            w = new Node(insertVal, nullptr);
            return w;
        }
        
        int minVal = w->val;
        Node *minNode = w;
        while(w->next != head) {
            w = w->next;
            if (minVal > w->val) {
                minNode = w;
                minVal = w->val;
            }
        }
        
        if (insertVal <= minVal) {
            w = minNode;
            while(w->next != minNode) {
                w = w->next;
            }
        } else {
            w = minNode;
            while(w->next != minNode && w->next->val < insertVal) {
                w = w->next;
            }
        }
        
        w->next = new Node(insertVal, w->next);
        return head;
    }
};
