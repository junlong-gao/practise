
#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include <cstdlib>
#include <iostream>

using namespace std;
class Solution {
    int curBest = 0;
    int helper(TreeNode* root){
        if(root == NULL) return 0;
        int left = helper(root->left);
        int right = helper(root->right);
        int tmp = 1;
        if(root->right != NULL && root->val == root->right->val - 1){
            tmp = max(tmp, right+1);
        }
        if(root->left != NULL && root->val == root->left->val - 1){
            tmp = max(tmp, left+1);
        }
        curBest = max(curBest, max(left, max(right,tmp)));
        return tmp;
    }
public:
    int longestConsecutive(TreeNode* root) {
        helper(root);
        return curBest;
    }
};


#endif //PRACTISE_SOLUTION_H
