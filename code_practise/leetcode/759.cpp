/*
 * [761] Employee Free Time
 *
 * https://leetcode.com/problems/employee-free-time/description/
 *
 * algorithms
 * Hard (51.89%)
 * Total Accepted:    3K
 * Total Submissions: 5.8K
 * Testcase Example:  '[[[1,2],[5,6]],[[1,3]],[[4,10]]]'
 *
 *
 * We are given a list schedule of employees, which represents the working time
 * for each employee.
 *
 * Each employee has a list of non-overlapping Intervals, and these intervals
 * are in sorted order.
 *
 * Return the list of finite intervals representing common, positive-length
 * free time for all employees, also in sorted order.
 *
 *
 * Example 1:
 *
 * Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
 * Output: [[3,4]]
 * Explanation:
 * There are a total of three employees, and all common
 * free time intervals would be [-inf, 1], [3, 4], [10, inf].
 * We discard any intervals that contain inf as they aren't finite.
 *
 *
 * Example 2:
 *
 * Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
 * Output: [[5,6],[7,9]]
 *
 *
 *
 *
 * (Even though we are representing Intervals in the form [x, y], the objects
 * inside are Intervals, not lists or arrays.  For example,
 * schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is
 * not defined.)
 *
 * Also, we wouldn't include intervals like [5, 5] in our answer, as they have
 * zero length.
 *
 *
 * Note:
 * schedule and schedule[i] are lists with lengths in range [1, 50].
 * 0 .
 *
 */
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
        vector<Interval> ret;
        int starting = INT_MAX;
        for (const auto & l : schedule) {
           if (l.empty()) continue;
           starting = std::min(starting, l[0].start);
        }

        for (const auto & l : schedule) {
           vector<Interval> list;
           for (int i = 0; i < l.size(); ++i) {
              if (i == 0) {
                 list.push_back({starting, l[i].start});
              } else {
                 list.push_back({l[i-1].end, l[i].start});
              }
           }

           list.push_back({l.back().end, INT_MAX});

           if (ret.empty()) {
              std::swap(ret, list);
           } else {
              vector<Interval> tmp;
              for (int i = 0; i < ret.size(); ++i) {
                 vector<Interval> tt;
                 for (int j = 0; j < list.size(); ++j) {
                    Interval t {
                       std::max(ret[i].start, list[j].start),
                       std::min(ret[i].end, list[j].end)
                    };
                    if (t.start >= t.end) continue;
                    //cout << t.start << " " << t.end << endl;
                    tt.push_back(t);
                 }

                 int k = 0, l = 0;
                 vector<Interval> in;
                 while (k < tt.size() && l < tmp.size()) {
                    Interval target;
                    if (tt[k].start < tmp[l].start) {
                       target = tt[k++];
                    } else {
                       target = tmp[l++];
                    }

                    if (in.empty()) {
                       in.push_back(target);
                    } else {
                       auto &d = in.back();
                       if (d.start > target.end || d.end < target.start) {
                          in.push_back(target);
                       } else {
                          d.start = std::min(d.start, target.start);
                          d.end = std::max(d.end, target.end);
                       }
                    }
                 }

                 while (k < tt.size()) {
                    in.push_back(tt[k++]);
                 }

                 while (l < tmp.size()) {
                    in.push_back(tmp[l++]);
                 }

                 std::swap(in, tmp);
              }
              std::swap(ret, tmp);
           }
        }

        if (ret.empty()) return ret;

        if (ret.back().end == INT_MAX) ret.pop_back();
        return ret;
    }
};


/*
TESTS
[[[1,2],[5,6]], [[3, 4]]]
[[[1,2],[5,6]],[[1,3]],[[4,10]]]
[[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
[[[1, 2]], [[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
[[[45,56],[89,96]],[[5,21],[57,74]]]
*/
