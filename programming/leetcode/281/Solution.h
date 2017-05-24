#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H

#include<vector>
#include<deque>
#include<list>

using namespace std;

class ZigzagIterator {
    list<deque<int>> l;
    list<deque<int>>::iterator ptr;
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if(!v1.empty()) l.emplace_back(v1.begin(), v1.end());
        if(!v2.empty()) l.emplace_back(v2.begin(), v2.end());
        ptr = l.begin();
    }

    int next() {
        int ret = (*ptr).front();
        (*ptr).pop_front();
        if((*ptr).empty()){
            ptr = l.erase(ptr);
        }else{
            ++ptr;
        }
        if(ptr == l.end()) ptr = l.begin();
        return ret;
    }

    bool hasNext() {
        return !l.empty();
    }
};


#endif //PRACTISE_SOLUTION_H
