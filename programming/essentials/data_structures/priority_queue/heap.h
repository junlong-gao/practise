//
// Created by Junlong Gao on 8/19/16.
//

#ifndef PRACTISE_HEAP_H_H
#define PRACTISE_HEAP_H_H
#include<functional>
#include<vector>
#include<algorithm>
#include<iostream>
#include "catch.hpp"

namespace priority_queue{
    template <typename T>
    class binary_heap{
        std::function<bool(T, T)> less_than;
        std::vector<T> data;
        T dummy;
        void heapfy(int idx){
            while(true){
                int l = idx * 2;
                int r = idx * 2 + 1;
                int largest = idx;
                if(l < data.size() && less_than(data[idx], data[l])){
                    largest = l;
                }
                if(r < data.size() && less_than(data[largest], data[r])){
                    largest = r;
                }
                if(largest != idx){
                    std::swap(data[idx], data[largest]);
                    idx = largest;
                }else{
                    break;
                }
            }
        }
        void init_heap(){
            for(int i = data.size() / 2; i > 0; --i){
                heapfy(i);
            }
        }
        void float_up(int idx){
            while(idx / 2 > 0){
                int p = idx / 2;
                if(less_than(data[p], data[idx])){
                    std::swap(data[p], data[idx]);
                }
                idx = p;
            }
        }
    public:
        binary_heap(std::function<bool(T,T)> comp){
            data.push_back(dummy);
            less_than = comp;
        }
        template <typename inputIterator>
        binary_heap(inputIterator begin, inputIterator end, std::function<bool(T,T)> comp){
            data.push_back(dummy);
            less_than = comp;
            while(begin != end){
                data.push_back(*(begin++));
            }
            init_heap();
        }
        bool empty(){
            return data.size() == 1;
        }
        T top(){
            if(empty()){
                throw std::runtime_error("heap underflow");
            }
            return data[1];
        }
        void pop(){
            if(empty()){
                throw std::runtime_error("heap underflow");
            }
            std::swap(data[1], data[data.size() - 1]);
            data.pop_back();
            heapfy(1);
        }
        void push(T obj){
            data.push_back(obj);
            float_up(data.size() - 1);
        }
        void update_keys(){
            init_heap();
        }
        void sort(){
            std::sort(data.begin() + 1, data.end(), less_than);
        }
        int size(){
            return data.size() - 1;
        }
        void printer(){
            for(int i = 1; i < data.size(); ++i){
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
    };

    bool test(std::vector<int> input, std::function<bool(int, int)> comp){
        binary_heap<int> testObj(input.begin(), input.end(), comp);
        sort(input.begin(), input.end(), comp);
        testObj.printer();
        for(int i = 0; i < input.size(); ++i){
            if(testObj.empty() && input[i] != testObj.top()){
                return false;
            }
            testObj.pop();
        }
        return true;
    }
    TEST_CASE("smoke test"){
        SECTION("integers"){
            REQUIRE(test({1,2,3,4}, [&](int l, int r){
                return l < r;
            }));
        }
        SECTION("fancy integers"){
            std::vector<int> rank = {1,2,3,4};
            REQUIRE(test({0,1,2,3}, [&](int l, int r){
                return rank[l] < rank[r];
            }));
        }
    }

}
#endif //PRACTISE_HEAP_H_H
