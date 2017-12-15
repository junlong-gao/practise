#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
    
     struct Interval {
         int start;
         int end;
         Interval() : start(0), end(0) {}
         Interval(int s, int e) : start(s), end(e) {}
     };
     
    struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
    class Solution {
    public:
        vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
            vector<Interval> output;
            int i = 0;
            while(i < intervals.size() &&
                  ((newInterval.end < intervals[i].start) || (newInterval.start > intervals[i].end))
                  && (newInterval.start > intervals[i].start)){
                output.push_back(intervals[i]);
                i++;
            }
            while(i < intervals.size() &&
                  ((newInterval.end >= intervals[i].start) && (newInterval.start <= intervals[i].end))){
                newInterval.start = min(newInterval.start, intervals[i].start);
                newInterval.end = max(newInterval.end, intervals[i].end);
                i++;
            }
            output.push_back(newInterval);
            while(i < intervals.size()){
                output.push_back(intervals[i]);
                i++;
            }
            return output;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){

		}
	}
}


