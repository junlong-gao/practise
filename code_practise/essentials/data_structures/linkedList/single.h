//
// Created by Junlong Gao on 8/21/16.
//

#ifndef PRACTISE_SINGLE_H
#define PRACTISE_SINGLE_H

#include <vector>

namespace linkedList{
    using namespace std;
    struct singlyLinked{
        int val;
        singlyLinked* next;
        singlyLinked(int val):val(val), next(nullptr){}
        ~singlyLinked(){
            delete next;
        }
    };

    singlyLinked* populate_single(vector<int>& data, int i){
        if(i >= data.size()) return nullptr;
        auto ret = new singlyLinked(data[i]);
        ret->next = populate_single(data, i+1);
        return ret;
    }

}
#endif //PRACTISE_SINGLE_H
