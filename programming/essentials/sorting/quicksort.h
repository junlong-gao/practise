//
// Created by Junlong Gao on 8/21/16.
//

#ifndef PRACTISE_QUICKSORT_H
#define PRACTISE_QUICKSORT_H
#include <vector>
#include <algorithm>
#include "catch.hpp"
#include "../linkedList/single.h"
#include "../linkedList/doubly.h"
namespace sorting{
    using namespace std;
    using namespace linkedList;

    singlyLinked* partition(singlyLinked* list, singlyLinked* start, singlyLinked* end){
        singlyLinked* i = start->next, *j = i;
        singlyLinked* probj = start;
        int pivit = start->val;
        while(i != end){
            if(i->val <= pivit){
                swap(i->val, j->val);
                j = j->next;
                probj = probj->next;
            }
            i = i->next;
        }
        int tmp = probj->val;
        probj->val = pivit;
        start->val = tmp;
        return probj;
    }
    void quicksort(singlyLinked* array, singlyLinked* start, singlyLinked* end){
        if(start == end) return;
        singlyLinked* pivit = partition(array, start, end);
        quicksort(array, start, pivit);
        quicksort(array, pivit->next, end);
    }

    doublyLinked* partition(doublyLinked* list, doublyLinked* start, doublyLinked* end){
        auto i = start->next, j = end;
        while(i != j){
            if(i->val > start->val){
                j = j->prev;
                swap(i->val, j->val);
            }
            else i = i->next;
        }
        swap(start->val, i->prev->val);
        return i->prev;
    }
    void quicksort(doublyLinked* array, doublyLinked* start, doublyLinked* end){
        if(start == end) return;
        doublyLinked* pivit = partition(array, start, end);
        quicksort(array, start, pivit);
        quicksort(array, pivit->next, end);
    }

    int partition(vector<int>& array, int start, int end){
        int i = start + 1, j = end;
        while(i < j){
            if(array[i] > array[start]) swap(array[i], array[--j]);
            else ++i;
        }
        swap(array[start], array[i-1]);
        return i - 1;
    }
    void quicksort(vector<int>& array, int start, int end){
        if(start >= end) return;
        int pivit = partition(array, start, end);
        quicksort(array, start, pivit);
        quicksort(array, pivit+1, end);
    }

    TEST_CASE("quick sort, array"){
        SECTION("smoke"){
            vector<int> testcase = {5,4,3,2,1};
            quicksort(testcase, 0, testcase.size());
            auto copy = testcase;
            sort(copy.begin(), copy.end());
            for(int i = 0; i < testcase.size(); ++i){
                REQUIRE(copy[i] == testcase[i]);
            }
        }
    }

    TEST_CASE("quick sort, singly linked list"){
        SECTION("smoke"){
            vector<int> testcase = {3, 4, 2,1};
            singlyLinked* head = populate_single(testcase, 0);
            quicksort(head, head, nullptr);
            singlyLinked* rst = head;
            sort(testcase.begin(), testcase.end());
            for(int i = 0; i < testcase.size(); ++i){
                REQUIRE(testcase[i] == rst->val);
                rst = rst->next;
            }
            delete head;
        }
    }

    TEST_CASE("quick sort, doubly linked list"){
        SECTION("smoke"){
            vector<int> testcase = {3,1,2};
            auto list = populate_double(testcase, 0);
            auto head = list.first;
            auto tail = list.second;
            quicksort(head, head, tail);
            doublyLinked* rst = head;
            sort(testcase.begin(), testcase.end());
            for(int i = 0; i < testcase.size(); ++i){
                REQUIRE(testcase[i] == rst->val);
                rst = rst->next;
            }
            delete head;
        }
    }
}
#endif //PRACTISE_QUICKSORT_H
