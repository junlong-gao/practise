class MyStack {
    deque<int> q;
public:
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
       q.push_back(x);
        int sz = q.size();
        while (sz > 1) {
            q.push_back(q.front()); q.pop_front();
            sz--;
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
       int ret = q.front();
        q.pop_front();
        return ret;
    }
    
    /** Get the top element. */
    int top() {
        return q.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
       return q.empty(); 
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */