//
// Created by Junlong Gao on 8/21/16.
//

#ifndef PRACTISE_MERGESORT_H
#define PRACTISE_MERGESORT_H

#include <vector>
#include "../linkedList/single.h"
#include "catch.hpp"

namespace sorting{
    using namespace std;
    using namespace linkedList;

    singlyLinked* merge(singlyLinked* l, singlyLinked* r){
        if(l == nullptr) return r;
        if(r == nullptr) return l;
        if(l->val > r->val){
            r->next = merge(l, r->next);
            return r;
        }else{
            l->next = merge(l->next, r);
            return l;
        }
    }

    singlyLinked* split(singlyLinked* list){
        singlyLinked* start = list;
        singlyLinked* fast = start->next;
        while(fast != nullptr){
            fast = fast->next;
            if(fast != nullptr){
                start = start->next;
                fast = fast->next;
            }
        }
        singlyLinked* ret = start->next;
        start->next = nullptr;
        return ret;
    }

    singlyLinked* mergesort(singlyLinked* list){
        if(list == nullptr || list->next == nullptr) return list;
        singlyLinked* mid = split(list);
        singlyLinked* l = mergesort(list);
        singlyLinked* r = mergesort(mid);
        return merge(l, r);
    }

    void merge(int start, int mid, int end, vector<int>& data){
        int i = start, j = mid;
        vector<int> tmp;
        while(i < mid && j < end){ tmp.push_back(data[i] > data[j]? data[j++] : data[i++]); }
        while(i < mid){ tmp.push_back(data[i++]); }
        while(j < end){ tmp.push_back(data[j++]); }
        for(int k = start; k < end; ++k){
            data[k] = tmp[k - start];
        }
    }

    void mergesort(int start, int end, vector<int>& data){
        if(start + 1 >= end) return;
        int mid = start + (end -start)/2;
        mergesort(start, mid, data);
        mergesort(mid, end, data);
        merge(start, mid, end, data);
    }

    TEST_CASE("mergesort, array"){
        SECTION("simple"){
            vector<int> testcase = {3,4,2,1};
            mergesort(0, testcase.size(), testcase);
            auto copy = testcase;
            sort(copy.begin(), copy.end());

            for(int i = 0; i < testcase.size(); ++i){
                REQUIRE(copy[i] == testcase[i]);
            }
        }
    }

    TEST_CASE("mergesort, singly linked"){
        SECTION("simple"){
            vector<int> testcase = {3,4,2,1};
            auto list = populate_single(testcase, 0);
            auto ret = mergesort(list);
            sort(testcase.begin(), testcase.end());

            for(int i = 0; i < testcase.size(); ++i){
                REQUIRE(ret->val == testcase[i]);
                ret = ret->next;
            }
            delete ret;
        }
    }
}
#endif //PRACTISE_MERGESORT_H
