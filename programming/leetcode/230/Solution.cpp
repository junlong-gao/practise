//
// Created by Junlong Gao on 8/1/16.
//

#include "Solution.h"
#include <iostream>
#include <cassert>

int main(){
    TreeNode root(1);
    TreeNode node2(2);
    TreeNode node3(3);
    root.right = &node2;
    node2.right = &node3;
    Solution test;
    assert(2 == test.kthSmallest(&root, 2));



}