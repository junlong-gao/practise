#include <iostream>
#include <unordered_map>
using namespace std;

struct TreeNode {
  TreeNode *left, *right;
  int val;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {;}
};

class Solution {
  int best = 0;

  void helper(TreeNode *root,
              int d,
              unordered_map<int, int> &ds,
              int tail) {
    if (root == nullptr) return;

    int newTail = tail;
    int oldVal =  -1;
    if (ds.count(root->val) == 1) {
       newTail = ds[root->val] + 1;
       oldVal = ds[root->val];
    }

    ds[root->val] = d;
    best = max(best, d - newTail + 1);

    helper(root->left, d + 1, ds, newTail);
    helper(root->right, d + 1, ds, newTail);

    if (oldVal != -1) {
      ds[root->val] = oldVal;
    } else {
      ds.erase(root->val);
    }
  }
public:
  int findMax(TreeNode *root) {
    unordered_map<int, int> ds;
    helper(root, 0, ds, 0);
    return best;
  }
};


int main() {
  {
    Solution s;
    TreeNode a(1), b(2), c(3), d(4);
    a.left = &b;
    b.left = &c;
    c.left = &d;
    cout << s.findMax(&a) << endl;
  }
  {
    Solution s;
    TreeNode a(1), b(1), c(3), d(4);
    a.left = &b;
    b.left = &c;
    c.left = &d;
    cout << s.findMax(&a) << endl;
  }

  {
    Solution s;
    TreeNode a(1), b(3), c(2), d(3);
    a.left = &b;
    a.right = &c;
    c.left = &d;
    cout << s.findMax(&a) << endl;
  }
  {
    Solution s;
    TreeNode a(1), b(1), c(3), d(2);
    a.left = &b; a.right = &d;
    b.left = &c;

    TreeNode e(1), f(2), g(2), h(3), i(3), j(1), k(4);
    d.left = &e; d.right = &g;
    e.left = &f; e.right = &h;
    g.left = &i; g.right = &j;
    h.right = &k;
    cout << s.findMax(&a) << endl;
  }
}
