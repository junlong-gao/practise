class RandomizedSet {
    unordered_map<int, int> lk;
    vector<int> e;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (lk.count(val)) return false;
        e.push_back(val);
        lk[val] = e.size() - 1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (lk.count(val) == 0) return false;
        int idx = lk[val];
        lk.erase(val);

        if (idx != e.size() - 1) {
            lk[e.back()] = idx;
            e[idx] = e.back();
        }
        e.pop_back();
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return e[rand()%e.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */