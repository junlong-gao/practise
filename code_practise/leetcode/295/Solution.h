//
// Created by junlong on 8/3/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include <queue>
#include <vector>

using namespace std;

//two heaps: up is larger or equal to lower
// use int to keep track of size

class MedianFinder {
    int upSize;
    int lowSize;
    priority_queue<int, std::vector<int>, std::less<int>> up;
    priority_queue<int, std::vector<int>, std::greater<int>> lower;
public:
    MedianFinder(){
        upSize = lowSize = 0;
    }

    // Adds a number into the data structure.
    void addNum(int num) {
        if(!lower.empty() && num > lower.top()){
            lower.push(num);
            lowSize++;
        }else if (!up.empty() && num <= up.top()){
            up.push(num);
            upSize++;
        }else{
            lower.push(num);
            lowSize++;
        }
        if(lowSize - upSize == 2){
            int top = lower.top();
            lower.pop();
            lowSize --;
            up.push(top);
            upSize++;
        }
        if(upSize - lowSize == 2){
            int top = up.top();
            up.pop();
            upSize --;
            lower.push(top);
            lowSize++;
        }

    }

    // Returns the median of current data stream
    double findMedian() {
        if(upSize == lowSize){
            return ((double)up.top() + (double)lower.top())/2;
        }else{
            return lowSize > upSize? lower.top(): up.top();
        }
    }
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();

#endif //PRACTISE_SOLUTION_H
