/*
> leetcode submit 715.cpp
  ✔ Accepted
  ✔ 53/53 cases passed (305 ms)
  ✔ Your runtime beats 20.56 % of cpp submissions
 * [715] Range Module
 *
 * https://leetcode.com/problems/range-module/description/
 *
 * algorithms
 * Hard (31.65%)
 * Total Accepted:    3.1K
 * Total Submissions: 9.8K
 * Testcase Example:  '["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange"]\n[[],[10,20],[14,16],[10,14],[13,15],[16,17]]'
 *
 * A Range Module is a module that tracks ranges of numbers. Your task is to
 * design and implement the following interfaces in an efficient manner.
 *
 * addRange(int left, int right) Adds the half-open interval [left, right),
 * tracking every real number in that interval.  Adding an interval that
 * partially overlaps with currently tracked numbers should add any numbers in
 * the interval [left, right) that are not already tracked.
 *
 * queryRange(int left, int right) Returns true if and only if every real
 * number in the interval [left, right)
 * ⁠is currently being tracked.
 *
 * removeRange(int left, int right) Stops tracking every real number currently
 * being tracked in the interval [left, right).
 *
 * Example 1:
 *
 * addRange(10, 20): null
 * removeRange(14, 16): null
 * queryRange(10, 14): true (Every number in [10, 14) is being tracked)
 * queryRange(13, 15): false (Numbers like 14, 14.03, 14.17 in [13, 15) are not
 * being tracked)
 * queryRange(16, 17): true (The number 16 in [16, 17) is still being tracked,
 * despite the remove operation)
 *
 *
 *
 * Note:
 * A half open interval [left, right) denotes all real numbers left .
 *
 * 0 < left < right < 10^9 in all calls to addRange, queryRange, removeRange.
 * The total number of calls to addRange in a single test case is at most 1000.
 * The total number of calls to queryRange in a single test case is at most
 * 5000.
 * The total number of calls to removeRange in a single test case is at most
 * 1000.
 *
 * Digestion: maintain a disjoint set of intervals
 * The tricky part: inserting and removing
 * Use idea of merge sort:
 * When inserting, maintain two ordered list of disjoint intervals
 *    Two intervals are mergable if and only if A.right <= B.left and
 *    A.left >= B.right (otherwise they are disjoint with non empty gap)
 *
 * When removing, same idea, but instead of merge, we subtract the intersection
 *    of A and B from A, which is just A \ B.
 */
class RangeModule {
   struct interval {
      int left, right;
   };

   vector<interval> s_;
   int clip (int left) {
      int lo = -1, hi = s_.size() - 1;
      while (hi - lo > 1) {
         int mid = lo + (hi - lo) / 2;
         if (s_[mid].right <= left) {
            lo = mid;
         } else {
            hi = mid;
         }
      }

      return hi;
   }

public:
    void dump(string s) {
       cout << s << endl;
       for(auto i : s_) {
          cout << "[" << i.left << ", " << i.right << ") ";
       }
       cout << endl;
    }
    RangeModule() { }

    void addRange(int left, int right) {
       vector<interval> t{interval{left, right}}, s;
       int i = 0, j = 0;

       while (j < t.size() && i < s_.size()) {
          if (t[j].left > s_[i].right) { // XXX equal 
             s.push_back(s_[i]);
             i++;
          } else if (s_[i].left > t[j].right) { // XXX equal
             s.push_back(t[j]);
             j++;
          } else {
             // merge
             t[j].left = std::min(t[j].left, s_[i].left);
             t[j].right = std::max(t[j].right, s_[i].right);
             i++;
          }
       }
       while (i < s_.size()) {
          s.push_back(s_[i++]);
       }
       while (j < t.size()) {
          s.push_back(t[j++]);
       }
       std::swap(s, s_);
       //dump(string("added ") + "[" + to_string(left) + "," + to_string(right) + ")");
    }

    bool queryRange(int left, int right) {
       if (s_.empty() || s_.front().left >= right || s_.back().right <= left) {
          return false;
       }
       int p = clip(left);
       return s_[p].left <= left && s_[p].right >= right;
    }

    void removeRange(int left, int right) {
       vector<interval> t{interval{left, right}}, s;
       int i = 0, j = 0;
       while (j < t.size() && i < s_.size()) {
          if (t[j].left >= s_[i].right) {
             s.push_back(s_[i]);
             i++;
          } else if (s_[i].left >= t[j].right) {
             j++;
          } else {
             // find intersection
             interval tmp;
             tmp.left = std::max(t[j].left, s_[i].left);
             tmp.right = std::min(t[j].right, s_[i].right);
             // remove the intersection from s_[i]
             interval leftp{0, 0}, rightp{0, 0};
             if (s_[i].left != tmp.left) {
                s.push_back(interval{s_[i].left, tmp.left});
             }
             if (s_[i].right != tmp.right) {
                s.push_back(interval{tmp.right, s_[i].right});
             }
             i++;
          }
       }
       while (i < s_.size()) {
          s.push_back(s_[i++]);
       }
       std::swap(s, s_);
       //dump(string("removed ") + "[" + to_string(left) + "," + to_string(right) + ")");
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule obj = new RangeModule();
 * obj.addRange(left,right);
 * bool param_2 = obj.queryRange(left,right);
 * obj.removeRange(left,right);
 */


/*
 *
["RangeModule","addRange", "addRange","addRange","queryRange"]
[[],[1,2],[6,7],[4,5], [4, 5]]
["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange","removeRange","removeRange","removeRange","addRange","addRange","addRange","removeRange","addRange","queryRange"]
[[],[14,100],[1,8],[77,80],[8,43],[4,13],[3,9],[45,49],[41,90],[58,79],[4,83],[34,39],[84,100],[8,9],[32,56]]
["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange"]
[[],[10,20],[14,16],[10,14],[13,15],[16,17]]
["RangeModule","addRange","queryRange","removeRange","queryRange","removeRange","addRange","queryRange","removeRange","addRange"]
[[],[8,9],[1,8],[1,8],[5,8],[3,9],[8,9],[4,5],[2,9],[5,6]]
["RangeModule", "queryRange", "queryRange", "addRange", "addRange", "queryRange", "queryRange", "queryRange", "removeRange", "addRange", "removeRange", "addRange", "removeRange", "removeRange", "queryRange", "queryRange", "queryRange", "queryRange", "removeRange", "addRange", "removeRange", "queryRange", "addRange", "addRange", "removeRange", "queryRange", "removeRange", "removeRange", "removeRange", "addRange", "removeRange", "addRange", "queryRange", "queryRange", "queryRange"]
[[],[21,34],[27,87],[44,53],[69,89],[23,26],[80,84],[11,12],[86,91],[87,94],[34,52],[1,59],[62,96],[34,83],[11,59],[59,79],[1,13],[21,23],[9,61],[17,21],[4,8],[19,25],[71,98],[23,94],[58,95],[12,78],[46,47],[50,70],[84,91],[51,63],[26,64],[38,87],[41,84],[19,21],[18,56]]
["RangeModule","addRange","addRange","addRange","addRange", "addRange", "queryRange"]
[[],[1,4],[8,9],[17,21],[71,98],[23,98], [21, 23]]
["RangeModule","queryRange","queryRange","addRange","addRange","queryRange","queryRange","queryRange","removeRange","addRange","removeRange","addRange","removeRange","removeRange","queryRange","queryRange","queryRange","queryRange","removeRange","addRange","removeRange","queryRange","addRange","addRange","removeRange","queryRange","removeRange","removeRange","removeRange","addRange","removeRange","addRange","queryRange","queryRange","queryRange","queryRange","queryRange","addRange","removeRange","addRange","addRange","addRange","queryRange","removeRange","addRange","queryRange","addRange","queryRange","removeRange","removeRange","addRange","addRange","queryRange","queryRange","addRange","addRange","removeRange","removeRange","removeRange","queryRange","removeRange","removeRange","addRange","queryRange","removeRange","addRange","addRange","queryRange","removeRange","queryRange","addRange","addRange","addRange","addRange","addRange","removeRange","removeRange","addRange","queryRange","queryRange","removeRange","removeRange","removeRange","addRange","queryRange","removeRange","queryRange","addRange","removeRange","removeRange","queryRange"]
[[],[21,34],[27,87],[44,53],[69,89],[23,26],[80,84],[11,12],[86,91],[87,94],[34,52],[1,59],[62,96],[34,83],[11,59],[59,79],[1,13],[21,23],[9,61],[17,21],[4,8],[19,25],[71,98],[23,94],[58,95],[12,78],[46,47],[50,70],[84,91],[51,63],[26,64],[38,87],[41,84],[19,21],[18,56],[23,39],[29,95],[79,100],[76,82],[37,55],[30,97],[1,36],[18,96],[45,86],[74,92],[27,78],[31,35],[87,91],[37,84],[26,57],[65,87],[76,91],[37,77],[18,66],[22,97],[2,91],[82,98],[41,46],[6,78],[44,80],[90,94],[37,88],[75,90],[23,37],[18,80],[92,93],[3,80],[68,86],[68,92],[52,91],[43,53],[36,37],[60,74],[4,9],[44,80],[85,93],[56,83],[9,26],[59,64],[16,66],[29,36],[51,96],[56,80],[13,87],[42,72],[6,56],[24,53],[43,71],[36,83],[15,45],[10,48]]
["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange","removeRange","removeRange","removeRange","addRange","addRange","addRange","removeRange","addRange","queryRange"]
[[],[14,100],[1,8],[77,80],[8,43],[4,13],[3,9],[45,49],[41,90],[58,79],[4,83],[34,39],[84,100],[8,9],[32,56]]
["RangeModule","addRange","removeRange","queryRange","queryRange","queryRange","removeRange","removeRange","removeRange","addRange"]
[[],[14,100],[1,8],[77,80],[8,43],[4,13],[3,9],[45,49],[41,90],[58,79]]
["RangeModule","addRange","removeRange","removeRange","removeRange","queryRange","removeRange","removeRange","addRange","queryRange","removeRange","addRange","addRange","queryRange","removeRange","queryRange","addRange","addRange","addRange","addRange","addRange","removeRange","removeRange","addRange","queryRange","queryRange","removeRange","removeRange","removeRange","addRange","queryRange","removeRange","queryRange","addRange","removeRange","removeRange","queryRange"]
[[],[2,91],[82,98],[41,46],[6,78],[44,80],[90,94],[37,88],[75,90],[23,37],[18,80],[92,93],[3,80],[68,86],[68,92],[52,91],[43,53],[36,37],[60,74],[4,9],[44,80],[85,93],[56,83],[9,26],[59,64],[16,66],[29,36],[51,96],[56,80],[13,87],[42,72],[6,56],[24,53],[43,71],[36,83],[15,45],[10,48]]
*/
/*
TESTS
["RangeModule","queryRange","queryRange","addRange","addRange","queryRange","queryRange","queryRange","removeRange","addRange","removeRange","addRange","removeRange","removeRange","queryRange","queryRange","queryRange","queryRange","removeRange","addRange","removeRange","queryRange","addRange","addRange","removeRange","queryRange","removeRange","removeRange","removeRange","addRange","removeRange","addRange","queryRange","queryRange","queryRange","queryRange","queryRange","addRange","removeRange","addRange","addRange","addRange","queryRange","removeRange","addRange","queryRange","addRange","queryRange","removeRange","removeRange","addRange","addRange","queryRange","queryRange","addRange","addRange","removeRange","removeRange","removeRange","queryRange","removeRange","removeRange","addRange","queryRange","removeRange","addRange","addRange","queryRange","removeRange","queryRange","addRange","addRange","addRange","addRange","addRange","removeRange","removeRange","addRange","queryRange","queryRange","removeRange","removeRange","removeRange","addRange","queryRange","removeRange","queryRange","addRange","removeRange","removeRange","queryRange"]
[[],[21,34],[27,87],[44,53],[69,89],[23,26],[80,84],[11,12],[86,91],[87,94],[34,52],[1,59],[62,96],[34,83],[11,59],[59,79],[1,13],[21,23],[9,61],[17,21],[4,8],[19,25],[71,98],[23,94],[58,95],[12,78],[46,47],[50,70],[84,91],[51,63],[26,64],[38,87],[41,84],[19,21],[18,56],[23,39],[29,95],[79,100],[76,82],[37,55],[30,97],[1,36],[18,96],[45,86],[74,92],[27,78],[31,35],[87,91],[37,84],[26,57],[65,87],[76,91],[37,77],[18,66],[22,97],[2,91],[82,98],[41,46],[6,78],[44,80],[90,94],[37,88],[75,90],[23,37],[18,80],[92,93],[3,80],[68,86],[68,92],[52,91],[43,53],[36,37],[60,74],[4,9],[44,80],[85,93],[56,83],[9,26],[59,64],[16,66],[29,36],[51,96],[56,80],[13,87],[42,72],[6,56],[24,53],[43,71],[36,83],[15,45],[10,48]]
*/
