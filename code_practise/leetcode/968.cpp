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
    unordered_map<TreeNode*, int> dp1, dp2, dp3;
    /*
    C1(r) : opt placement count of subtree r completely covered except r
    C2(r) : opt placement count of subtree r completely covered, but
            no camera at r
    C3(r) : opt placement count of subtree r completely covered and
            there is a camera at r
            
    C1(empty) = C2(empty) = 0
    C3(empty) = 1
    
    C1(tree) = C2(tree->left) + C2(tree->right)}
    C2(tree) = min{ min{C2(tree->left), C3(tree->left)} + C3(tree->right),
                    C3(tree->left) + min{C2(tree->right), C3(tree->right)}}
    C3(tree) = 1 + min{C1/C2/C3(tree->left)} + min{C1/C2/C3(tree->right)}
    
    ans = min{C2(root), C3(root)}
    */
    int C1(TreeNode* tree);
    int C2(TreeNode* tree);
    int C3(TreeNode* tree);

public: 
    int minCameraCover(TreeNode* root) {
        return min(C2(root), C3(root));
    }
};

int Solution::C1(TreeNode* tree) {
    if (tree == nullptr) return 0;
    if (dp1.count(tree)) return dp1[tree];
    return dp1[tree] = C2(tree->left) + C2(tree->right);
}

int Solution::C2(TreeNode* tree) {
    if (tree == nullptr) return 0;
    if (dp2.count(tree)) return dp2[tree];
    return dp2[tree] = 
        min(C3(tree->left) + min(C2(tree->right), C3(tree->right)),
            min(C2(tree->left), C3(tree->left)) + C3(tree->right));
}

int Solution::C3(TreeNode* tree) {
    if (tree == nullptr) return 1;
    if (dp3.count(tree)) return dp3[tree];
    return dp3[tree] = 
        1 + min(C1(tree->left), min(C2(tree->left), C3(tree->left)))
          + min(C1(tree->right), min(C2(tree->right), C3(tree->right)));
}

/*
Testcases
[1,null,2,3,null,4,5,null,null,6]
[0,0,null,0,0]
[]
[0]
[0,0]
[0, null, 0]
[0,0,null,0,null,0,null,null,0]
[0,null,0,0,null,0,0,null,null,0]
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,null,null,0,null,0,0,0,0,null,null,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,null,0,null,0,0,0,0,0,0,0,0,null,0,0,0,0,0,0,0,null,0,0,0,0,0,null,0,0,0,0,0,0,null,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,null,null,null,null,0,0,null,0,0,0,null,0,0,0,0,0,0,0,null,0,0,0,null,null,0,0,0,0,null,null,0,0,0,0,0,0,0,0,0,0,0,0,null,null,null,null,0,0,0,0,null,null,0,null,0,0,0,0,0,0,null,0,0,0,null,null,0,0,0,0,0,null,0,0,0,0,0,null,null,null,0,0,0,0,0,0,null,null,0,0,0,0,0,0,null,0,0,0,0,0,0,null,0,0,0,0,0,0,null,0,0,0,null,null,null,null,0,0,0,0,0,null,null,null,0,0,0,0,0,0,0,null,0,0,0,null,0,0,0,0,0,0,0,0,0,0,0,null,0,null,null,null,0,null,null,null,null,null,null,0,null,0,0,0,0,null,0,0,null,0,0,0,null,0,null,null,null,null,null,null,null,0,0,null,0,0,null,null,0,0,0,null,0,0,null,null,null,null,0,0,null,0,0,0,0,0,0,0,null,null,0,0,0,0,0,null,null,0,null,0,null,null,0,0,null,0,0,0,0,0,0,null,0,0,0,0,0,null,0,null,0,0,0,0,0,0,0,0,0,null,0,0,0,0,0,0,0,0,0,0,0,0,0,0,null,0,0,null,null,0,0,null,null,null,0,null,0,0,0,0,null,0,0,0,null,null,null,null,null,null,0,0,0,0,0,null,0,0,null,null,0,0,null,0,null,null,0,null,null,0,null,0,0,0,0,0,0,null,0,null,null,null,null,0,null,0,null,0,null,null,null,null,0,0,null,0,null,0,null,0,null,0,0,null,null,0,0,0,null,0,0,null,null,0,null,null,null,null,null,0,0,0,0,0,0,0,0,0,0,null,null,null,null,null,null,0,null,0,null,null,null,null,0,0,0,null,null,0,0,0,null,0,null,0,0,null,0,null,null,0,null,null,null,0,0,0,0,0,0,0,0,0,null,0,0,null,0,null,null,0,0,0,0,null,null,0,null,null,0,null,0,0,0,0,0,0,null,0,null,null,0,null,null,0,0,null,null,null,0,0,0,0,0,0,0,0,0,0,0,0,null,0,0,0,0,0,0,null,0,0,0,0,0,0,null,0,0,0,null,null,0,0,null,null,0,0,0,null,0,null,null,null,null,0,0,null,null,null,null,null,null,null,0,0,null,null,null,null,0,null,0,null,0,null,null,0,null,null,null,null,null,0,null,null,null,null,null,null,0,0,null,null,0,null,null,0,null,null,null,0,0,0,0,null,null,null,null,null,null,0,null,0,null,null,0,0,null,null,null,null,null,null,0,null,0,0,null,null,0,null,null,null,null,null,0,null,null,null,0,0,null,null,null,0,null,null,null,null,null,null,null,null,0,null,null,0,0,0,0,0,null,null,null,null,0,null,0,0,0,0,0,0,null,null,null,null,0,0,0,0,0,0,null,null,0,0,0,0,0,0,0,0,0,0,0,null,null,null,null,0,0,0,null,null,null,null,null,0,null,null,null,0,null,null,null,null,0,0,null,0,null,0,null,0,0,0,null,0,null,0,null,null,null,null,0,0,0,0,0,0,null,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,null,0,0,0,0,0,null,null,null,null,null,null,null,null,null,0,0,null,0,0,null,null,0,0,null,null,null,null,null,null,null,null,null,null,null,null,null,0,null,0,null,null,null,null,null,null,0,null,null,null,null,null,0,null,null,null,0,0,null,0,0,0,0,0,0,0,0,0,0,null,null,0,null,0,null,0,0,null,null,0,null,0,0,null,null,0,null,0,0,0,0,null,null,null,null,null,null,null,0,null,null,null,0,null,null,0,0,0,0,0,0,0,null,null,null,null,null,null,0,0,0,null,0,null,null,0,0,null,null,null,0,0,null,0,null,0,0,0,0,0,null,0,0,null,null,0,null,0,0,0,null,null,null,null,null,null,0,0,null,null,null,0,null,0,0,0,0,0,0,null,null,null,null,0,null,null,null,null,null,null,0,0,0,null,null,null,null,null,0,0,null,null,0,0,0,0,0,0,0,null,null,null,null,null,null,null,0,0,null,0,0,0,null,null,null,0,null,null,0,0,0,0,0,0,null,null,0,0,0,0,0,0,0,0,null,null,null,null,null,null,null,null,0,0,0,null,null,null,null,null,0,0,null,null,0,0,null,null,null,null,null,0,0,null,null,null,0,0,null,null,0,null,0,null,null,null,null,0,null,null,null,null,null,null,null,null,null,null,null,0,0,0,null,null,null,null,null,null,null,0,0,null,null,null,null,0,0,0,0,null,0,0,null,null,null,null,null,null,0,0,0,0,null,null,null,null,0,null,null,null,null,null,null,null,0,null,null,null,null,0,null,null,null,null,null,null,null,0,null,null,0,0,0,0,0,0,0,0,0,null,0,null,null,null,null,null,null,null,0,0,null,null,null,null,null,0,null,null,null,0,null,null,null,0,null,null,null,null,null,null,null,null,0,null,null,0,null,null,0,0,0,0,null,0,0,null,0,null,0,0,0,0,null,null,0,0,0,0,0,0,null,null,0,null,null,null,null,null,null,null,0,0,0,0,0,null,0,0,0,0,null,null,null,0,null,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,null,null,null,null,0,0,null,null,null,null,null,null,null,null,null,0,0,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,0,0,null,0,null,null,0,null,null,0,0,null,0,null,null,0,0,0,null,0,0,null,null,null,null,0,null,null,null,0,0,0,0,0,null,0,0,0,0,0,0,0,null,0,null,null,null,0,null,null,null,null,null,null,null,null,null,null,null,0,0,0,0,0,0,0,0,null,null,null,null,0,null,null,0,0,0,null,null,0,0,0,0,null,0,0,null,null,0,0,0,null,0,0,null,0,0,0,0,0,0,0,null,0,0,0,null,0,null,0,0,null,null,null,null,null,0,0,null,0,null,0,0,null,0,0,null,null,null,null,0,0,0,null,null,null,0,null,null,0,0,null,0,null,0,null,null,0,0,null,null,null,0,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,0,null,null,null,null,null,null,null,null,null,null,null,null,0,0,0,0,null,null,null,0,null,null,null,null,0,null,null,0,null,0,null,null,null,0,null,0,0,0,null,null,0,null,0,null,null,null,0,null,null,null,null,null,null,null,null,0,0,0,null,0,0,0,null,0,null,0,0,0,null,null,0,0,0,null,null,null,null,null,0,null,0,null,0,0,0,0,0,null,0,0,0,null,null,0,null,null,0,0,null,null,null,0,0,null,null,null,null,null,null,0,null,null,0,0,0,null,null,null,0,null,null,0,null,null,null,null,0,null,null,0,0,null,null,0,null,null,0,0,null,null,null,null,null,0,null,null,0,null,null,null,null,null,null,null,null,null,null,0,0,0,null,null,null,0,0,0,0,0,0,null,null,0,null,null,null,null,null,0,0,0,null,0,null,null,null,null,null,null,0,0,0,0,0,null,0,0,0,null,null,0,null,null,null,0,null,null,0,null,null,0,0,0,null,0,null,null,0,0,null,null,0,null,null,0,null,null,null,0,null,null,0,0,0,0,0,0,0,0,null,null,0,0,0,null,null,null,null,0,null,null,0,0,null,null,null,null,null,null,null,null,null,null,0,0,null,null,null,0,null,0,0,0,null,null,null,null,0,null,0,null,0,null,0,null,null,null,null,null,0,0,null,0,null,0,0,0,0,0,null,null,0,0,null,0,null,null,0,null,0,0,0,null,null,null,null,null,null,null,0,null,null,null,null,0,0,0,null,null,null,null,0,null,null,null,0,null,0,null,0,null,0,null,null,null,null,0,null,0,null,0,null,null,0,0,null,null,0,0,null,null,null,null,0,0,null,null,null,null,null,null,0,null,null,0,null,null,null,null,null,0,0,null,null,0,null,null,0,null,null,null,0,null,0,null,0,0,null,null,null,0,null,null,null,null,null,null,0,null,null,null,0,null,null,null,null,0,0,null,null,null,null,null,null,null,null,0,null,0,null,null,0,null,null,null,null,0,0,null,null,null,null,0,0,0,null,null,0,null,null,0,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,0,null,null,null,null,null,0,null,null,null,null,null,null,null,null,null,null,null,0,null,null,null,null,null,0]
*/
