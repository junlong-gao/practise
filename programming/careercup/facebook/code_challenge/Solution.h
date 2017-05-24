//
// Created by Junlong Gao on 8/16/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <iostream>
#include "../../catch.hpp"

namespace {
    using namespace std;
    struct Node{
        int val;
        Node* next;
        Node(int _val = 0): val(_val), next(nullptr){}
        ~Node(){
            if(next){
                delete next;
            }
            next = nullptr;
        }
    };

    class SingleLinkedList{
        Node* head;
        Node* tail;
    public:
        SingleLinkedList():head(nullptr), tail(nullptr){}

        Node* &front(){
            return head;
        }
        Node* &back(){
            return tail;
        }

        void push(int val){
            if(head == nullptr){
                head = new Node(val);
                tail = head;
            }else{
                tail->next = new Node(val);
                tail = tail->next;
            }
        }
        //destructor
        ~SingleLinkedList(){
            delete head;
        }
    };

    Node* Merge(Node* &l, Node* &r){
        if(l == nullptr) return r;
        if(r == nullptr) return l;
        Node* ret = nullptr;
        if(l->val <= r->val){
            ret = l;
            ret->next = Merge(l->next, r);
        }else{
            ret = r;
            ret->next = Merge(l, r->next);
        }
        return ret;
    }

    void MergeSort(Node* &listHead){
        if(listHead == nullptr || listHead->next == nullptr) return;
        Node* slow = listHead;
        Node* fast = slow->next;
        while(fast != nullptr){
            fast = fast->next;
            if(fast != nullptr){
                slow = slow->next;
                fast = fast->next;
            }
        }
        Node* mid = slow->next;
        slow->next = nullptr;
        MergeSort(listHead);
        MergeSort(mid);

        listHead = Merge(listHead, mid);
    }

    bool test(vector<int> testArray){
        SingleLinkedList testObj;
        for(auto val: testArray){
            testObj.push(val);
        }
        MergeSort(testObj.front());
        sort(testArray.begin(), testArray.end());
        Node* ptr = testObj.front();
        for(auto val: testArray){
            if(ptr == nullptr || ptr->val != val){
                return false;
            }
            ptr = ptr->next;
        }
        return true;
    }

    TEST_CASE("test"){
        SECTION("edge case: 1 element"){
            REQUIRE(test({1}));
        }
        SECTION("edge case: 2 elements"){
            REQUIRE(test({2,1}));
        }
        SECTION("smoke test"){
            REQUIRE(test({4,3,2,1}));
        }
        SECTION("shuffle smoke test"){
            REQUIRE(test({5,3,4,1,2}));
        }

    }
}


#endif //PRACTISE_SOLUTION_H
