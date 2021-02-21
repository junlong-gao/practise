class AllOne {
    list<pair<unordered_set<string>, int>> data;
    unordered_map<string, list<pair<unordered_set<string>, int>>::iterator> index;
public:
    /** Initialize your data structure here. */
    AllOne() {

    }

    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        auto ptr = index.find(key);
        if (ptr == index.end()) {
            if (data.empty() || data.begin()->second != 1) {
               data.push_front({{key}, 1});
            } else {
                data.begin()->first.insert(key);
            }
            index[key] = data.begin();
        } else {
            auto listPtr = ptr->second;
            auto nextNodePtr = std::next(ptr->second);
            auto newVal = listPtr->second + 1;

            index.erase(key);
            listPtr->first.erase(key);
            if (listPtr->first.empty()) {
                data.erase(listPtr);
            }

            if (nextNodePtr != data.end() && nextNodePtr->second == newVal) {
                nextNodePtr->first.insert(key);
                index[key] = nextNodePtr;
            } else {
                index[key] = data.insert(nextNodePtr, {{key}, newVal});
            }
        }
    }

    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        auto ptr = index.find(key);
        if (ptr == index.end()) {
            return;
        }

        auto listPtr = ptr->second;
        auto newVal = listPtr->second - 1;

        if (newVal) {
            if (listPtr == data.begin() || std::prev(listPtr)->second != newVal) {
                index[key] = data.insert(listPtr, {{key}, newVal});
            } else {
                std::prev(listPtr)->first.insert(key);
                index[key] = std::prev(listPtr);
            }
        } else {
            index.erase(key);
        }

        listPtr->first.erase(key);
        if (listPtr->first.empty()) {
            data.erase(listPtr);
        }
    }

    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (data.empty()) {
            return "";
        } else {
            assert(data.rbegin()->first.size());
            return *(data.rbegin()->first.begin());
        }
    }

    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (data.empty()) {
            return "";
        } else {
            assert(data.begin()->first.size());
            return *(data.begin()->first.begin());
        }
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
