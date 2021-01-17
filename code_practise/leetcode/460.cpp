class LFUCache {
    class LRUCache {
        struct ent_t {
          int key, val;  
        };
        list<ent_t> data;
        unordered_map<int, list<ent_t>::iterator> pt;
        int notFound = -1;
        
        list<ent_t>::iterator ref(int key) {
            assert(pt.count(key));
            auto ent = *pt[key];
            data.erase(pt[key]);
            data.push_front(ent);
            pt[key] = data.begin();
            return data.begin();
        }
    public:
        int size() {
            return data.size();
        }
        
        int& get(int key) {
            if (pt.count(key)) {
                return ref(key)->val;
            }
            return notFound;
        }
        
        void put(int key, int val) {
            if (pt.count(key)) {
                ref(key)->val = val;
            } else {
                data.push_front(ent_t{key, val});
                pt[key] = data.begin();
            }
        }
        
        int evict() {
            int ret = data.back().key;
            pt.erase(ret);
            data.pop_back();
            return ret;
        }
        
        int remove(int key) {
            assert(pt.count(key));
            int ret = pt[key]->val;
            
            data.erase(pt[key]);
            pt.erase(key);
            
            return ret;
        }
    };
    
    unordered_map<int, int> refcount;
    map<int, LRUCache> buckets;
    int n, cap;
    
    int& ref(int key) {
        int val = buckets[refcount[key]].remove(key);
        if (buckets[refcount[key]].size() == 0) {
            buckets.erase(refcount[key]);
        }
        refcount[key]++;
        buckets[refcount[key]].put(key, val);
        return buckets[refcount[key]].get(key);
    }
public:
    LFUCache(int capacity) {
        n = 0;
        cap = capacity;
    }
    
    int get(int key) {
        if (cap == 0) {
            return -1;
        }
        
        if (refcount.count(key)) {
            return ref(key);
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (cap == 0) {
            return;
        }
        
        if (refcount.count(key)) {
            ref(key) = value;
        } else {
            if (n == cap) {
                int lfuKey = buckets.begin()->second.evict();
                n--;
                refcount.erase(lfuKey);
                if (buckets.begin()->second.size() == 0) {
                    buckets.erase(buckets.begin());
                }
            }
            n++;
            refcount[key] = 1;
            buckets[refcount[key]].put(key, value);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */