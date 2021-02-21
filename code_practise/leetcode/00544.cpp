
/*
1 2 3 4 5 6 7 8
8 7 6 5
8 7
8

(1, 8) -> 8
(2, 7) -> 7
(3, 6) -> 6
(4, 5) -> 5

(5, 8) -> 8
(6, 7) -> 7

(7, 8)

(((3, 6), (2, 7)),  ((4, 5), (1, 8)))
*/

class Solution {
	struct TreeNode {
		int val;
		TreeNode* l; TreeNode* r;
		~TreeNode() {
			delete l;
			delete r;
		}
	};

	string print(TreeNode *node) {
		if (node == nullptr) return "";
		if (node->l == nullptr && node->r == nullptr) return to_string(node->val);
		if (node->l->l == nullptr) {
			return "(" + print(node->r) + "," + print(node->l) + ")";
		}
		return "(" + print(node->l) + "," + print(node->r) + ")";
	}
public:
    string findContestMatch(int n) {
            deque<TreeNode*> init;
	for (int i = n; i >=1; --i) {
		init.push_back(new TreeNode{i, nullptr, nullptr});
	}
// 8 7 6 5 4 3 2 1

	while (init.size() > 1) {
		deque<TreeNode*> tmp;
		for (int i = 0; i < init.size() / 2; ++i) {
			int j = init.size() - 1 - i;
			tmp.push_back(new TreeNode{init[i]->val, init[i], init[j]});
			// 8 7 6 5
		}
		std::swap(tmp, init);
	}

	string ret = print(init.front());

	delete init.front();
	return ret;
    }
};

