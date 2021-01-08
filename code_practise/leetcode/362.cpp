class HitCounter {
    int total = 0;
    const int fiveMin = 300;
    struct ent_t {
        int tt;
        int count;
    };
    deque<ent_t> hits;
public:
    /** Initialize your data structure here. */
    HitCounter() {
        
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        total++;
        if (hits.size() && hits.back().tt == timestamp) {
            hits.back().count++;
        } else {
            hits.push_back(ent_t{timestamp, 1});
        }
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        while (hits.size() && (timestamp - hits.front().tt >= fiveMin)) {
            total -= hits.front().count;
            hits.pop_front();
        }
        return total;
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
