class MyCalendarTwo {
	map<int, int> evs;
    

public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
	int cur = 0;
	evs[start]++;
	evs[end]--;

    for (auto it = evs.begin(); it != evs.end(); ++it) {
		cur += it->second;
        if (it->first > end) break;
		if (cur > 2) {
			evs[start]--;
			evs[end]++;
			return false;
		}
	}

	return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo obj = new MyCalendarTwo();
 * bool param_1 = obj.book(start,end);
 */

