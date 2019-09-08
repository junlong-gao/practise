/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};
*/
class Solution {
    pair<Node*, Node*> helper(Node* h) {
        Node* t = h, *p = h;
        while (t) {
            if (t->child) {
                auto r = helper(t->child);
                Node *n = t->next;
                t->next = r.first;
                t->child = nullptr;
                r.first->prev = t;
                r.second->next = n;
                if (n) {
                   n->prev = r.second;
                }
                p = r.second;
                t = n;
            } else {
                p = t;
                t = t->next;
            }
        }
        return make_pair(h, p);
    }
public:
    Node* flatten(Node* head) {
        return helper(head).first;
    }
};
