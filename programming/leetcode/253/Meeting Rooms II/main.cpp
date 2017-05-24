//
//  main.cpp
//  Meeting Rooms II
//
//  Created by John on 9/27/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
	int minMeetingRooms(vector<Interval>& intervals) {
		map<int, int> changes;
		for (auto i : intervals) {
			changes[i.start] += 1;
			changes[i.end] -= 1;
		}
		int rooms = 0, maxrooms = 0;
		for (auto change : changes)
			maxrooms = max(maxrooms, rooms += change.second);
		return maxrooms;
	}
};

int main(int argc, const char * argv[]) {
    Solution mine;
    vector<Interval> tests;
    tests.push_back(Interval(2, 15));
     tests.push_back(Interval(36, 45));
     tests.push_back(Interval(9, 29));
     tests.push_back(Interval(16, 23));
    tests.push_back(Interval(4, 9));
    //tests.push_back(Interval(19, 21));
    //tests.push_back(Interval(21, 23));
    //tests.push_back(Interval(25, 27));
    // tests.push_back(Interval(9, 16));
    
    cout<<mine.minMeetingRooms(tests);
	// insert code here...
	//std::cout << "Hello, World!\n";
    return 0;
}
