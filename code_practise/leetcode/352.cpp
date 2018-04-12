/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class SummaryRanges {
    vector<Interval> s_; // original
    
    /* set<int> points_; // follow up */
public:
    /** Initialize your data structure here. */
    SummaryRanges() { ; }
    
    vector<Interval> merge(const vector<Interval>& ins, const vector<Interval> &r) {
        vector<Interval> out;
        int i = 0, j = 0;
        auto f = [&out](const Interval & source) {
            if (out.empty()) {
                out.push_back(source);
                return;
            }
            
            if (out.back().end + 1 >= source.start) {
                out.back().end = std::max(out.back().end, source.end);
            } else {
                out.push_back(source);
            }
        };
        
        while (i < r.size() && j < ins.size()) { 
            if (r[i].start < ins[j].start) { f(r[i]);  i++;  }
            else { f(ins[j]); j++; }
        }
        
        while (i < r.size()) { f(r[i]); i++; }
        
        while (j < ins.size()) { f(ins[j]); j++; }
        
        return out;
    }
    void addNum(int val) {
        /* points_.insert(val); // follow up */
        
        s_ = merge(s_, {Interval{val, val}}); // original
    }
    
    vector<Interval> getIntervals() {
        /*
        return merge([&]() {
            vector<Interval> ret;
            for (const auto & v : points_) {
                ret.push_back(Interval{v, v});
            }
            return ret;
        }(), {}); // follow up
        */
        
        return s_; // original
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */
/*

original:
add(): O(n)
get(): O(1) + copy the whole result... return by ref?

Follow up:
What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?

lots of merges -> add() cannot be too costy
the number of disjoint intervals are small -> get() can be costy

to reduce add, use O(logn) for insertion of points (no merge), and maintain order
get will have to calculate the disjoint intervals on the fly (do a merge on get)

*/
