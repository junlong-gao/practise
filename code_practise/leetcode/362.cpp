class HitCounter {
	struct Hit {
		int t;
		int count;
		Hit (int t_, int count_) : t(t_), count(count_) {;}
	};
	deque<Hit> window;
	int counter {0};
	static constexpr int WINDOW_SIZE {300};
public:
    /** Initialize your data structure here. */
    HitCounter() {
        
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
	counter ++;
            if (window.empty() || window.back().t != timestamp) {
		window.emplace_back(timestamp, 1);
/*
XXX2
forget to early return here.
or should just use explicit else
	}
	window.back().count++;
*/
	} else {
		window.back().count++;
	}
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
/*
XXX1 this is wrong. as time as progressed to timestamp, not window.back().t
so when called by timestamp > window.back().t you are wrong.
            while (!window.empty() && window.back().t - window.front().t + 1 > WINDOW_SIZE) {
*/
            while (!window.empty() && timestamp - window.front().t + 1 > WINDOW_SIZE) {
		counter -= window.front().count;
		window.pop_front();
	}
	return counter;
    }
};
