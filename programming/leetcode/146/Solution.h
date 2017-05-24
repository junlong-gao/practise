//
// Created by Junlong Gao on 7/29/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H

#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

class LRUCache {
    list<pair<int, int>> caches;
    unordered_map<int, list<pair<int,int>>::iterator> pointers;
    const size_t size;
    size_t curSize;

public:
    LRUCache(int capacity):size(capacity), curSize(0){;}

    list<pair<int, int>>::iterator getRef(int key){
        auto it = pointers.find(key);
        if(it==pointers.end()){
            return caches.end();
        }
        auto tmp = caches.begin();
        int tmpKey = tmp->first;
        if(tmpKey == key) return tmp; // try remove this line.

        caches.push_front(*(pointers[key]));
        caches.erase(it->second);

        pointers[key] = caches.begin();
        pointers[tmpKey] = tmp;

        return caches.begin();

    };

    int get(int key){
        auto ret = getRef(key);
        if(ret != caches.end()){
            return ret->second;
        }
        return -1;
    }

    void set(int key, int value){
        if(pointers.find(key)!=pointers.end()){
            auto target = getRef(key);
            target->second = value;
            return;
        }
        if(curSize >= size){
            int tmp = caches.back().first;
            caches.pop_back();
            pointers.erase(tmp);
            curSize--;
        }
        caches.push_front(make_pair(key, value));
        curSize++;
        pointers[key] = caches.begin();
    }
};


#endif //PRACTISE_SOLUTION_H
