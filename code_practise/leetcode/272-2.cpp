#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    using namespace std;
	class Solution {
    public:
        vector<int> closestKValues(TreeNode* root, double target, int k) {
            vector<double> nodes;
            vector<TreeNode*> stack;
            while(root){
                stack.push_back(root);
                root = root->left;
            }
            while(!stack.empty()){
                auto top = stack.back();
                stack.pop_back();
                nodes.push_back(top->val - target);
                top = top->right;
                while(top){
                    stack.push_back(top);
                    top = top->left;
                }
            }
            int i = 0;
            while(i < nodes.size() && nodes[i] < 0){
                i++;
            }
            if(i > 0 && i < nodes.size() && abs(nodes[i - 1]) < abs(nodes[i])){
                i--;
            }else if(i == nodes.size()){
                i--;
            }


            vector<int> rst;
            if(k == 0) return rst;
            if(nodes.empty()) return rst;
            rst.push_back(nodes[i] + target);
            int j = i - 1, l = i + 1;
            while(rst.size() < k){
                if(l < nodes.size() && j >= 0){
                    if(abs(nodes[j]) <= abs(nodes[l])){
                        rst.push_back(nodes[j] + target);
                        j--;
                    }else{
                        rst.push_back(nodes[l] + target);
                        l++;
                    }
                }else if(l < nodes.size()){
                    rst.push_back(nodes[l] + target);
                    l++;
                }else{
                    rst.push_back(nodes[j] + target);
                    j--;
                }
            }
            return rst;
        }

    };
	TEST_CASE("tests"){
        Solution testObj;
        TreeNode root{5}, left{1}, right{6};
        root.left = &left;
        root.right = &right;
        SECTION("sample"){
            auto rst = testObj.closestKValues(&root, 0.9, 1);
            unordered_set<int> expected{1};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(expected.find(rst[i]) != expected.end());
            }
        }
        SECTION("sample 2"){
            auto rst = testObj.closestKValues(&root, 2, 1);
            unordered_set<int> expected{1};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(expected.find(rst[i]) != expected.end());
            }
        }
        SECTION("sample 3"){
            auto rst = testObj.closestKValues(&root, 10, 1);
            unordered_set<int> expected{6};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(expected.find(rst[i]) != expected.end());
            }
        }
        SECTION("sample 4"){
            auto rst = testObj.closestKValues(&root, 10, 2);
            unordered_set<int> expected{5, 6};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(expected.find(rst[i]) != expected.end());
            }
        }
        SECTION("sample 5"){
            auto rst = testObj.closestKValues(&root, -10, 2);
            unordered_set<int> expected{5, 1};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(expected.find(rst[i]) != expected.end());
            }
        }
        SECTION("sample 6"){
            auto rst = testObj.closestKValues(&root, 5, 3);
            unordered_set<int> expected{5, 1, 6};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(expected.find(rst[i]) != expected.end());
            }
        }
        SECTION("sample 7"){
            TreeNode ll{-3}, lr{4}, rr{7};
            left.left = &ll;
            left.right = &lr;
            right.right = &rr;
            auto rst = testObj.closestKValues(&root, 5, 4);
            unordered_set<int> expected{5, 4, 6, 7};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(expected.find(rst[i]) != expected.end());
            }
        }
        SECTION("wa 1"){
            TreeNode root{3}, l{2}, r{4}, ll{1};
            root.left = &l;
            root.right = &r;
            l.left = &ll;
            auto rst = testObj.closestKValues(&root, 2, 3);
            unordered_set<int> expected{3,1,2};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(expected.find(rst[i]) != expected.end());
            }
        }
	}
}


