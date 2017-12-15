//
// Created by Junlong Gao on 8/21/16.
//

#ifndef PRACTISE_DOUBLY_H
#define PRACTISE_DOUBLY_H

#include <vector>

namespace linkedList{
    using namespace std;
    struct doublyLinked{
        int val;
        doublyLinked* next;
        doublyLinked* prev;
        doublyLinked(int val):val(val), next(nullptr), prev(nullptr){}
        ~doublyLinked(){
            delete next;
        }
    };

    pair<doublyLinked*, doublyLinked*> populate_double(vector<int>& data, int i){
        if(i >= data.size()) {
            auto dummy = new doublyLinked(0);
            return make_pair(dummy, dummy);
        }
        auto ret = new doublyLinked(data[i]);
        auto rst = populate_double(data, i+1);
        ret->next = rst.first;
        ret->next->prev = ret;
        return make_pair(ret, rst.second);
    }

}
#endif //PRACTISE_DOUBLY_H
