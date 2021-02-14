class DinnerPlates {
    map<int, vector<int>> ss;
    int idx = 0;
    int cap;
public:
    DinnerPlates(int capacity) {
        cap = capacity;
    }
    
    void push(int val) {
        for (auto it : ss) {
            if (it.second.size() < cap) {
                it.second.push_back(val);
                return;
            }
        }   
        ss[idx++].push_back(val);
    }
    
    int pop() {
        auto it = ss.rbegin();
        if (it == ss.rend()) {
            return -1;
        } else {
            int ret = it->second.back();
            it->second.pop_back();
            if (it->second.size() == 0) {
                ss.erase(it.base());
            }
            
            return ret;
        }
    }
    
    int popAtStack(int index) {
        auto it = ss.find(index);
        auto ret = it->second.back();
        it->second.pop_back();
        if (it->second.size() == 0) {
            ss.erase(it);
        }
        
        return ret;
    }
};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */