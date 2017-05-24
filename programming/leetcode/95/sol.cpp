/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    vector<TreeNode*> generateTree(vector<int>& values){
        //for(auto i:values){
        //    cout << i << " ";
        //}
        //cout << endl;
        if(values.size() == 0) return vector<TreeNode*>();
        if(values.size() == 1) return vector<TreeNode*>{new TreeNode{values.front()}};
        vector<TreeNode*> ret;
        for(size_t i = 0; i < values.size(); ++i){
            vector<int> l, r;
            for(size_t j = 0; j < i; ++j){
                l.push_back(values[j]);
            }
            for(size_t j = i + 1; j < values.size(); ++j){
                r.push_back(values[j]);
            }
            vector<TreeNode*> ls = generateTree(l), rs = generateTree(r);
            if(ls.empty()){
                for(auto rsubtree: rs){
                    TreeNode* root = new TreeNode(values[i]);
                    root->right = rsubtree;
                    ret.push_back(root);
                }
            }else if(rs.empty()){
                for(auto lsubtree: ls){
                    TreeNode* root = new TreeNode(values[i]);
                    root->left = lsubtree;
                    ret.push_back(root);
                }
            }else{
                for(auto lsubtree : ls){
                    for(auto rsubtree: rs){
                        TreeNode* root = new TreeNode(values[i]);
                        root->left = lsubtree; root->right = rsubtree;
                        ret.push_back(root);
                    }
                }
            }
        }
        return ret;
    }
public:
    vector<TreeNode*> generateTrees(int n){
        vector<int> v(n);
        std::iota (std::begin(v), std::end(v), 1);
        //for(auto i: v){
            //cout << i << " " ;
        //}
        return generateTree(v);
    }
};