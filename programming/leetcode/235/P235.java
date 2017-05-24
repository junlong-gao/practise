package com.junlonga.app.P235;

/**
 * Created by jungao on 7/24/16.
 */

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}

public class P235 {
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode p, TreeNode q) {
        if(root == null || root == p || root == q) return root;
        TreeNode leftRst = lowestCommonAncestor(root.left, p, q);
        TreeNode rightRst = lowestCommonAncestor(root.right, p, q);
        return leftRst == null ? rightRst : (rightRst == null ? leftRst : root);
    }
}
