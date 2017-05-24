#include <vector>
using namespace std;
class MinStack {
    vector<int> internal_stack;
    vector<int> mins;

public:
    /** initialize your data structure here. */
    MinStack() {

    }
    void push(int x) {
        internal_stack.push_back(x);
        if(mins.empty() || x <= mins.back()){
            mins.push_back(x);
        }
    }

    void pop() {
        if(!mins.empty() && internal_stack.back() == mins.back()){
            mins.pop_back();
        }
        internal_stack.pop_back();
    }

    int top() {
        return internal_stack.back();
    }

    int getMin() {
        return mins.back();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */