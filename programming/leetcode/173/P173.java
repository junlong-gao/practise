package com.junlonga.app.P173;

import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Created by jungao on 7/24/16.
 */
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}


public class P173 {
    ArrayDeque<TreeNode> leftBranch;
    public P173(TreeNode root) {
        this.leftBranch = new ArrayDeque<>();
        getLeftBranch(root);
    }

    void getLeftBranch(TreeNode root){
        TreeNode it = root;
        while(it!= null){
            leftBranch.addLast(it);
            it = it.left;
        }
    }
    /** @return whether we have a next smallest number */
    public boolean hasNext() {
        return leftBranch.isEmpty();
    }

    /** @return the next smallest number */
    public int next() {
        TreeNode last = leftBranch.pollLast();
        getLeftBranch(last.right);
        return last.val;
    }
}
