#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
    class Solution {
        void helper(map<int, vector<int>>& table,  TreeNode* root, int offset){
            if(root == nullptr){
                return;
            }
            deque<pair<TreeNode*, int>> Q;
            Q.push_back(make_pair(root, 0));
            while(!Q.empty()){
                int size = Q.size();
                for(int i = 0; i < size; ++i){
                    pair<TreeNode*, int> top = Q.front();
                    Q.pop_front();
                    table[top.second].push_back((top.first)->val);
                    if(top.first->left!=nullptr){
                        Q.push_back(make_pair((top.first)->left, top.second-1));
                    }
                    if(top.first->right!=nullptr){
                        Q.push_back(make_pair((top.first)->right, top.second+1));
                    }
                }
                
            }
            return;
        }
    public:
        vector<vector<int>> verticalOrder(TreeNode* root) {
            map<int, vector<int>> table;
            helper(table, root, 0);
            vector<vector<int>> rst;
            for(auto& pr : table){
                rst.push_back(pr.second);
            }
            return rst;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){

		}
	}
}


