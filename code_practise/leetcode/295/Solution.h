class MedianFinder {
    priority_queue<int, vector<int>, std::greater<int>> upper;
    priority_queue<int, vector<int>, std::less<int>> lower;

    template<typename T1, typename T2>
    void balance(T1& larger, T2& smaller){
        while(!larger.empty() && larger.size() - smaller.size() >= 2){
            auto top = larger.top(); larger.pop();
            smaller.push(top);
        }
    }
public:

    // Adds a number into the data structure.
    void addNum(int num) {
        if(lower.empty() || num <= lower.top()){
			lower.push(num);
        }else{
            upper.push(num);
        }
        
        if((int)(lower.size() - upper.size()) >= 2){
            balance(lower, upper);
        }
        
        if((int)(lower.size() - upper.size()) <= -2){
            balance(upper, lower);
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        if(upper.size() != lower.size()){
            return upper.size() > lower.size() ? 
                      (double)upper.top() :
                      (double)lower.top();
        }
        return (double)(upper.top() + lower.top())/2.0;
    }
};
