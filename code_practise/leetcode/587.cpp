/*
 * > leetcode submit 587.cpp
 *   ✔ Accepted
 *   ✔ 82/82 cases passed (28 ms)
 *   ✔ Your runtime beats 59.31 % of cpp submissions
 */

/*
 * [587] Erect the Fence
 *
 * https://leetcode.com/problems/erect-the-fence/description/
 *
 * algorithms
 * Hard (33.28%)
 * Total Accepted:    4.1K
 * Total Submissions: 12.2K
 * Testcase Example:  '[[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]'
 *
 * There are some trees, where each tree is represented by (x,y) coordinate in
 * a two-dimensional garden. Your job is to fence the entire garden using the
 * minimum length of rope as it is expensive. The garden is well fenced only if
 * all the trees are enclosed. Your task is to help find the coordinates of
 * trees which are exactly located on the fence perimeter.
 *
 * Example 1:
 *
 * Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
 * Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
 * Explanation:
 *
 *
 *
 *
 * Example 2:
 *
 * Input: [[1,2],[2,2],[4,2]]
 * Output: [[1,2],[2,2],[4,2]]
 * Explanation:
 *
 * Even you only have trees in a line, you need to use rope to enclose
 * them.
 *
 *
 *
 * ⁠Note:
 *
 * All trees should be enclosed together. You cannot cut the rope to enclose
 * trees that will separate them in more than one group.
 * All input integers will range from 0 to 100.
 * The garden has at least one tree.
 * All coordinates are distinct.
 * Input points have NO order. No order required for output.
 *
 *
 */
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

/*
 * Computational Geometry: Convex Hull
 * Let A be any simply polygon covers the set P, and let B be the convex hull of P.
 * If A differs from B, then there exists a segment XY on B so that if we extend
 * it to line l, and identify L, R as the left most, right most intersection of l.
 * Include L and R into A as new vertex if they are not.
 * As A differs from B, we can assume the part in A from L to R is different from
 * B, so we replace that part with segment LR, which results in better perimeter due
 * to triangle inequality.
 *
 * Graham Scan
 * 1. Sort points by x and y. The left most and right most must be on the convex hull
 * 2. Build the convex hull through 2 passes. The first path go from bottom left to right,
 *    the second path go from top right back to origin.
 *    During the path, use the already built first 2 points to check the new point
 *    is forming convex hull. If not, the already built first 2 must be unwind
 *    backwards until they form convex edge with the new point.
 *    To test, use det(a, b) <= 0. Note in this problem trees on the same line
 *    are also on the convex hull, so remove the equality.
 *    The second pass works the same, note we must go all the way back to origin
 *    to include the final origin back. This is because to form the convex hull,
 *    the origin (as the final point) to check with previous edge's convex edge
 *    must also be considered.
 *
 */
class Solution {
   int det(const Point &a, const Point &b) {
      return a.x * b.y - a.y * b.x;
   }

   Point vec(const Point &a, const Point &b) {
      return {a.x - b.x, a.y - b.y};
   }

   int dot(const Point &a, const Point &b) {
      return a.x * b.x + a.y * b.y;
   }

   bool same(const Point &a, const Point &b) {
      return (a.x == b.x && a.y == b.y);
   }

public:
    vector<Point> outerTrees(vector<Point>& points) {
       int k = 0, n = points.size();
       if (n <= 3) return points;

       std::sort(points.begin(), points.end(),
          [] (const Point &l, const Point &r) {
             if (l.x != r.x) {
                return l.x < r.x;
             }
             return l.y < r.y;
       });

       vector<Point> qs(2 * n); // <---- resize
       // if all points are co-linear, graham scan will only return 2 different points
       for (int i = 0; i < n; ++i) {
          while (k >= 2 && det(vec(qs[k-1], qs[k-2]), vec(points[i], qs[k-1])) < 0) k--;  // <---- add equality to discard points on the same line
          qs[k++] = points[i];
       }

       for (int i = n - 1, t = k; i >= 0; i--) { // <----- i still has to go down to 0
          // remember graham scan will construct and remove non-convex indexes,
          // the last point(the origin, points[0]) to include into the upper
          // path will go back to the first point (points[0]), and use that to
          // make sure the last part (back to origin) is still convex
          // it will be removed as it is duplicated
          while (k > t && det(vec(qs[k-1], qs[k-2]), vec(points[i], qs[k-1])) < 0) k--;
          qs[k++] = points[i];
       }

       // the last point(origin) reroute back to the origin can be removed from the list,
       // but we are to dedup anyway.
       qs.resize(k - 1);

       std::sort(qs.begin(), qs.end(),
          [] (const Point &l, const Point &r) {
             if (l.x != r.x) {
                return l.x < r.x;
             }
             return l.y < r.y;
       });

       int i = 0, j = i;
       while (j < qs.size()) {
          while (j < qs.size() && same(qs[i], qs[j])) { j++; }

          if (j < qs.size()) {
             i++;
             std::swap(qs[i], qs[j]);
             j++;
          } else {
             break;
          }
       }
       qs.resize(i + 1);

       /*

       if (qs.size() == 2) return points;
       */
       return qs;
    }
};


/*
TESTS
[[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
[[1,2],[2,2],[4,2]]
[[1,2],[2,2],[4,0], [3, 0]]
[[1,2],[2,2],[4,0], [0, 0], [1, 1]]
[[1,1],[2,2]]
[[1,1]]
*/
