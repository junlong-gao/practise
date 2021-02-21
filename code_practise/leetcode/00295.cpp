class MedianFinder {
    priority_queue<int, vector<int>, std::greater<int>> upper;
    priority_queue<int, vector<int>, std::less<int>> lower; // top largest
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if (upper.empty() || num > upper.top()) {
            upper.push(num);
            if (upper.size() > lower.size() + 1){
                lower.push(upper.top());
                upper.pop();
            }
        } else {
            lower.push(num);
            if (lower.size() > upper.size()) {
                upper.push(lower.top());
                lower.pop();
            }
        }
    }
    
    double findMedian() {
        if ((upper.size() + lower.size()) % 2) {
            return upper.top();
        }
        return (upper.top() + lower.top()) / 2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
