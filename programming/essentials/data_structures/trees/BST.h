//
// Created by Junlong Gao on 8/20/16.
//

#ifndef PRACTISE_BST_H
#define PRACTISE_BST_H
#include <iostream>
#include <vector>
#include "catch.hpp"
namespace trees{
    using namespace std;
    class BST{
        struct Node{
            int val;
            Node* left;
            Node* right;
            Node* p;
            Node(int val){
                this->val = val;
                p = left = right = nullptr;
            }
            ~Node(){
                delete left;
                delete right;
                right = left = nullptr;
            }
        };
        Node* root;
        int size;
        void transplant(Node* u, Node* v){
            if(u->p == nullptr){
                root = v;
            }else if (u->p->left == u){
                u->p->left = v;
            }else{
                u->p->right = v;
            }
            if(v != nullptr){
                v->p = u->p;
            }
        }
    public:
        BST(){
            size = 0;
            root = nullptr;
        }

        int get_size(){
            return size;
        }

        Node* get_root(){
            return root;
        }

        Node* search(int val){
            Node* z = root;
            while(z!=nullptr && z->val != val){
                if(val < z->val) z= z->left;
                else z= z->right;
            }
            return z;
        }
        Node* min_node(Node* z){
            while(z->left != nullptr){
                z = z->left;
            }
            return z;
        }
        Node* successor(Node* z){
            Node* p = nullptr;
            if(z->right == nullptr){
                p = z->p;
                while(p != nullptr && p->left != z){
                    z = p; p = z->p;
                }
                return p;
            }else{
                return min_node(z->right);
            }
        }
        Node* max_node(Node* z){
            while(z->right != nullptr){
                z = z->right;
            }
            return z;
        }
        Node* predecessor(Node* z){
            Node* p = nullptr;
            if(z->left == nullptr){
                p = z->p;
                while(p != nullptr && p->right != z){
                    z = p; p = z->p;
                }
                return p;
            }else{
                return max_node(z->left);
            }
        }
        Node* insert(int val){
            size++;
            Node* z = root;
            if(z == nullptr){
                root = new Node(val);
                return root;
            }
            Node* p = z->p;
            while(z!= nullptr){
                p = z;
                if(val < z->val) z = z->left;
                else z = z->right;
            }
            Node* to_ret = nullptr;
            if(p->val > val){
                p->left = new Node(val);
                to_ret = p->left;
            }else{
                p->right = new Node(val);
                to_ret = p->right;
            }
            to_ret->p = p;
            return to_ret;
        }
        Node* remove(Node* z){
            size--;
            if(z->right == nullptr){
                transplant(z, z->left);
            }else if(z->left == nullptr) {
                transplant(z, z->right);
            }else{
                Node* y = successor(z);
                Node* x = z->right;
                if(y != x){
                    transplant(x->left, y->right);
                    y->right = x;
                    y->right->p = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->p = y->left;
            }
            z->p = z->left = z->right = nullptr;
            return z;
        }
        ~BST(){
            delete root;
        }
    };
    void populate(vector<int> data, BST& tree){
        int previous_size = tree.get_size();
        for(int i = 0; i < data.size(); ++i){
            tree.insert(data[i]);
            REQUIRE(tree.search(data[i]) != nullptr);
            REQUIRE(tree.search(data[i])->val == data[i]);
            REQUIRE(tree.get_size() == ++previous_size);
        }
    }
    void existance(vector<int> data, BST& tree){
        int previous_size = tree.get_size();
        for(int i = 0; i < data.size(); ++i){
            REQUIRE(tree.search(data[i]) != nullptr);
            REQUIRE(tree.search(data[i])->val == data[i]);
            REQUIRE(tree.get_size() == previous_size);
        }
    }
    void destruction(vector<int> data, BST& tree){
        int previous_size = tree.get_size();
        for(int i = 0; i < data.size(); ++i){
            tree.remove(tree.search(data[i]));
            REQUIRE(tree.search(data[i]) == nullptr);
            REQUIRE(tree.get_size() == --previous_size);
       }
    }
    TEST_CASE("smoke test on bst"){
        BST tree = BST();
        SECTION("simple insert, search, delete"){
            vector<int> test_case = {1,2,3,4,5,6};
            populate(test_case, tree);
            existance(test_case, tree);
            destruction(test_case, tree);
        }
        SECTION("min, max"){
            populate({2,3,1,4,5}, tree);
            REQUIRE(tree.min_node(tree.get_root())->val == 1);
            REQUIRE(tree.max_node(tree.get_root())->val == 5);
        }
        SECTION("predecessor, successor") {
            vector<int> testcase = {1,2,3,4,6,5,7,0};
            populate(testcase, tree);
            sort(testcase.begin(), testcase.end());
            for(int i = testcase.size() - 1; i - 1 >= 0; --i){
                REQUIRE(tree.predecessor(tree.search(testcase[i])) != nullptr);
                REQUIRE(tree.predecessor(tree.search(testcase[i])) -> val == testcase[i-1]);
            }
            for(int i = 0; i + 1 < testcase.size(); ++i){
                REQUIRE(tree.successor(tree.search(testcase[i])) != nullptr);
                REQUIRE(tree.successor(tree.search(testcase[i])) -> val == testcase[i+1]);
            }
        }

    }
}
#endif //PRACTISE_BST_H
