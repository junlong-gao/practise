class MinStack {
    struct ent_t {
        int minv;
        int count;
    };
    vector<int> data;
    vector<ent_t> ms;
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        data.push_back(x);
        if (ms.empty()) {
            ms.push_back(ent_t{x, 1});
        } else {
            if (x < ms.back().minv) {
                ms.push_back(ent_t{x, 1});
            } else if (x == ms.back().minv) {
                ms.back().count++;
            }
        }
    }
    
    void pop() {
        int back = data.back(); data.pop_back();
        assert(back >= ms.back().minv);
        if (back == ms.back().minv) {
            ms.back().count--;
            if (ms.back().count == 0) {
                ms.pop_back();
            }
        }
    }
    
    int top() {
        return data.back();
    }
    
    int getMin() {
        return ms.back().minv;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */