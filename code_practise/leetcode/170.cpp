class TwoSum {
    unordered_map<int, int> container;
public:
    /** Initialize your data structure here. */
    TwoSum() {
        
    }
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        container[number]++;
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        bool found = false;
        for (auto pr : container) {
            container[pr.first]--;
            if (container.count(value - pr.first) > 0 && container[value - pr.first] > 0) {
                found = true;
            }
            container[pr.first]++;
            if (found) {
                break;
            }
        }
        return found;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */