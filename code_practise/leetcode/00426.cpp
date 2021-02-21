/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
    pair<Node*, Node*> helper(Node *root) {
        if (root == nullptr) {
            return make_pair(nullptr, nullptr);
        } else {
            //cout << root->val << endl;
            auto retl = helper(root->left);
            auto retr = helper(root->right);
            Node* head = nullptr, *tail = nullptr;
            if (retl.first == nullptr) {
                assert(retl.second == nullptr);
                head = root;
                root->left = nullptr; //
            } else {
                assert(retl.second);
                head = retl.first;
                retl.second->right = root;
                root->left = retl.second;
            }
            
            if (retr.first == nullptr) {
                assert(retr.second == nullptr);
                tail = root;
                root->right = nullptr; //
            } else {
                assert(retr.second);
                tail = retr.second;
                retr.first->left = root;
                root->right = retr.first;
            }
            
            if (root->left == nullptr && root->right == nullptr) {
                root->left = root;
                root->right = root;
            } else if (root->left == nullptr) {
                root->left = retr.second;
                retr.second->right = root;
            } else if (root->right == nullptr) {
                root->right = retl.first;
                retl.first->left = root;
            } else {
                retl.first->left = retr.second;
                retr.second->right = retl.first;
            }
            
            return make_pair(head, tail);
        }
    }
public:
    Node* treeToDoublyList(Node* root) {
        return helper(root).first;
    }
};
