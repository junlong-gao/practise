class LRUCache {
    struct ent {
        int key; int val;
    };
    list<ent> data;
    unordered_map<int, list<ent>::iterator> links;
    int cap_;
    list<ent>::iterator ref(int key) {
        if (links.count(key) == 0) {
            return data.end();
        }
        auto it = links[key];
        ent e = *it;
        data.erase(it);
        data.push_front(e);
        links[e.key] = data.begin();
        return data.begin();
    }
public:
    LRUCache(int capacity) {
        cap_ = capacity;
    }
    
    int get(int key) {
        auto it = ref(key);
        if (it != data.end()) {
            return it->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        auto it = ref(key);
        if (it != data.end()) {
            it->val = value;
            return;
        }
        if (data.size() == cap_) {
            auto victim = data.back();
            links.erase(victim.key);
            data.pop_back();
        }
        data.push_front(ent{key, value});
        links[key] = data.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
