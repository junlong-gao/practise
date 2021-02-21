class MovingAverage {
    int sum, cap;
    deque<int> vs;
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        sum = 0;
       cap = size; 
    }
    
    double next(int val) {
       if (vs.size() == cap) {
           sum -= vs.front();
           vs.pop_front();
       } 
       vs.push_back(val);
        sum += val;
        
        return (sum * 1.0) / (vs.size() * 1.0);
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
