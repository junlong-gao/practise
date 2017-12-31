
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [&](auto& l, auto& r){
            return l.start < r.start;
        });
        list<Interval> inter(intervals.begin(), intervals.end());
        auto ptr = inter.begin();
        while (ptr != inter.end()) {
            auto nptr = next(ptr, 1);
            if(nptr == inter.end()) break;
            if(nptr->start >= ptr->end){
                ptr->end = max(ptr->end, nptr->end);
                inter.erase(nptr);
            }else{
                ptr++;
            }
        }
        vector<Interval> merge(inter.begin(), inter.end());
        return merge;
    }
};