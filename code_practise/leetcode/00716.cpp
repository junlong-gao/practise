class MaxStack {
    map <int, vector<list<int>::iterator>> eles_;
    list<int> s_;
public:
    /** initialize your data structure here. */
    MaxStack() {
        
    }

    void push(int x) {
        s_.push_front(x);
        eles_[x].push_back(s_.begin());
    }
    
    int pop() {
        int x = s_.front();
        eles_[x].pop_back();
        if (eles_[x].empty()) {
            eles_.erase(x);
        }
        s_.pop_front();
        return x;
    }
    
    int top() {
        return s_.front();
    }
    
    int peekMax() {
        return eles_.rbegin()->first;
    }
    
    int popMax() {
        auto e = eles_.rbegin();
        int ret = e->first;
        s_.erase(e->second.back());
        e->second.pop_back();
        if (e->second.empty()) {
            eles_.erase(ret);
        }
        return ret;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack obj = new MaxStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.peekMax();
 * int param_5 = obj.popMax();
 */
