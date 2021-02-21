#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <deque>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"


struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
using namespace std; 
class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if(root->left!=nullptr){
            TreeNode* newRoot = root->left;
            TreeNode* rst = upsideDownBinaryTree(root->left);
            newRoot->left = root->right;
            newRoot->right = root;
            root->left = root->right = nullptr;
            if(root->right){
                root->right->left = root->right->right = nullptr;
            }
            return rst;
        }else{
            return root;
        }
    }
    void print(TreeNode* root){
        if(root){
            cout << root->val << " ";
            print(root->left);
            print(root->right);
        }
    }
};

int main(){
    std::ifstream in(FILENAME);
    if(DEBUG){
        std::cin.rdbuf(in.rdbuf());
    }
    TreeNode a1(1);
    TreeNode a2(2);
    TreeNode a3(3);
    TreeNode a4(4);
    TreeNode a5(5);
    a1.left = &a2; a1.right = &a3;
    a2.left = &a4; a2.right = &a5;
    Solution s;
    TreeNode* rst = s.upsideDownBinaryTree(&a1);
    s.print(rst);
    return 0;
}
