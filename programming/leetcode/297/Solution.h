class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        deque<TreeNode*> q;
        string s;
        q.push_back(root);
        while(!q.empty()){
            auto top = q.front();
            s += (top == NULL) ? "NULL" : to_string(top->val);
            s += " ";
            q.pop_front();
            if(top != NULL){
                q.push_back(top->left);
                q.push_back(top->right);
            }
        }
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream iss(data);
        string top; iss >> top;
        if(top == "NULL") return NULL;
        TreeNode* root = new TreeNode(atoi(top.c_str()));
        deque<TreeNode*> q; q.push_back(root);
        while(!q.empty()){
            int size = q.size();
            for(int i = 0; i < size; ++i){
                if(q.front() != NULL){
                    string left, right;
                    iss >> left >> right;
                    TreeNode* leftNode = (left == "NULL") ? NULL : new TreeNode(atoi(left.c_str()));
                    TreeNode* rightNode = (right == "NULL") ? NULL : new TreeNode(atoi(right.c_str()));
                    q.front()->left = leftNode;
                    q.front()->right = rightNode;
                    q.push_back(leftNode);
                    q.push_back(rightNode);
                }
                q.pop_front();
            }
        }
        return root;
    }
};