class LFUCache {
    using pr_t = pair<int, int>;
    using C_t = list<int>;
    int cap;
    int size;
    int cur_min_key;
    unordered_map<int, pr_t> kv;                //k->freq, value
    unordered_map<int, C_t::iterator> key_to_ptr; 
    unordered_map<int, C_t>  f_to_keyC; 

public:
    LFUCache(int capacity) {
        cap = capacity;
        size = 0;
    }
    
    int get(int key) {
        if(kv.find(key) == kv.end()) return -1;
        hit(key);
        return kv[key].second;
    }
    
    void put(int key, int value) {
        //test();
        if(cap == 0) return;
        if(kv.find(key) == kv.end()){
            if(size == cap){
                int f = kv[cur_min_key].first;
                kv.erase(cur_min_key);
                assert(f_to_keyC[f].back() == cur_min_key);
                f_to_keyC[f].erase(key_to_ptr[cur_min_key]);
                key_to_ptr.erase(key);
                size--;
            }
            kv[key] = make_pair(1, value);
            size++;
            f_to_keyC[1].push_front(key);
            key_to_ptr[key] = f_to_keyC[1].begin();
            cur_min_key = f_to_keyC[1].back(); //
        }else{
            hit(key);
            kv[key].second = value;
        }
        //test();
    }
    
    void hit(int key){
        //test();
        int f = kv[key].first;
        kv[key].first++;
        f_to_keyC[f].erase(key_to_ptr[key]);
        f_to_keyC[f+1].push_front(key);
        key_to_ptr[key] = f_to_keyC[f+1].begin();
        //update min:
        if(cur_min_key == key){
            if(!f_to_keyC[f].empty()){
                cur_min_key = f_to_keyC[f].back();
            }else{
                cur_min_key = f_to_keyC[f+1].back();
            }
        }
        //test();
    }
    
    void test(){
        //invariant
        if(kv.size() == 0) return;
        assert(f_to_keyC[kv[cur_min_key].first].back() == cur_min_key);
    }
    
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */