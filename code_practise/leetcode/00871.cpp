/*
 * @lc app=leetcode id=871 lang=cpp
 *
 * [871] Minimum Number of Refueling Stops
 *
 * https://leetcode.com/problems/minimum-number-of-refueling-stops/description/
 *
 * algorithms
 * Hard (30.66%)
 * Likes:    501
 * Dislikes: 9
 * Total Accepted:    12.3K
 * Total Submissions: 39.9K
 * Testcase Example:  '1\n1\n[]'
 *
 * A car travels from a starting position to a destination which is target
 * miles east of the starting position.
 * 
 * Along the way, there are gas stations.  Each station[i] represents a gas
 * station that is station[i][0] miles east of the starting position, and has
 * station[i][1] liters of gas.
 * 
 * The car starts with an infinite tank of gas, which initially has startFuel
 * liters of fuel in it.  It uses 1 liter of gas per 1 mile that it drives.
 * 
 * When the car reaches a gas station, it may stop and refuel, transferring all
 * the gas from the station into the car.
 * 
 * What is the least number of refueling stops the car must make in order to
 * reach its destination?  If it cannot reach the destination, return -1.
 * 
 * Note that if the car reaches a gas station with 0 fuel left, the car can
 * still refuel there.  If the car reaches the destination with 0 fuel left, it
 * is still considered to have arrived.
 * 
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: target = 1, startFuel = 1, stations = []
 * Output: 0
 * Explanation: We can reach the target without refueling.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: target = 100, startFuel = 1, stations = [[10,100]]
 * Output: -1
 * Explanation: We can't reach the target (or even the first gas station).
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: target = 100, startFuel = 10, stations =
 * [[10,60],[20,30],[30,30],[60,40]]
 * Output: 2
 * Explanation: 
 * We start with 10 liters of fuel.
 * We drive to position 10, expending 10 liters of fuel.  We refuel from 0
 * liters to 60 liters of gas.
 * Then, we drive from position 10 to position 60 (expending 50 liters of
 * fuel),
 * and refuel from 10 liters to 50 liters of gas.  We then drive to and reach
 * the target.
 * We made 2 refueling stops along the way, so we return 2.
 * 
 * 
 * 
 * 
 * Note:
 * 
 * 
 * 1 <= target, startFuel, stations[i][1] <= 10^9
 * 0 <= stations.length <= 500
 * 0 < stations[0][0] < stations[1][0] < ... < stations[stations.length-1][0] <
 * target
 * 
 * 
 * 
 * 
 * 
 */

// @lc code=start
class Solution {
   /*
    * let b_k be the maximal distance to reach from start with k refills.
    * let p be the collection of un-used stations to the left of b
    * let q be the collection of stations to the right of b. target is in
    * q.
    *
    * initially, b = startFuel, k = 0, p is the collection of
    * reachable stations before startFuel, and q is the rest.
    *
    * consider example:
    * startFuel = 2, target = 4, station = [s1 = (1, 1), s2 = (2, 1)]
    * The only way is to refill at both.
    *
    * From the collection of p, use the maximal fuel in it so we know
    * we can reach b + max(p) with k + 1 refills. Remove it from collection
    * of p, and add elements in q into p.
    * Repeat this process until b covers target.
    *
    * Because the algorithm terminates exactly when b >= target. b_1 < target
    * but b_2 >= target means with k you cannot reach target (b_1 is the max),
    * and with k + 1 refill you can reach target. If you can reach target with
    * less than k + 1 (i.e. at most k refill), then b_1 >= target (note b_k is
    * a non-decreasing function of k).
    * 
    * Using the above example:
    * b = 2, k = 0, p = [(1, 1), (2, 1)], q = []
    * --> b < target
    *
    * b = 3, k = 1, p = [(1, 1)], q = []
    * --> b < target
    *
    * b = 4, k = 2, p = [], q = []
    * --> b >= target
    */
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
       int b = startFuel; priority_queue<int> p; int q = 0; int k = 0;
       while (q < stations.size() && stations[q][0] <= b) {
          p.push(stations[q++][1]);
       }
       while (b < target && p.size()) {
          b += p.top(); p.pop();
          k++;
          while (q < stations.size() && stations[q][0] <= b) {
             p.push(stations[q++][1]);
          }
       }
       return b < target ? -1: k;
    }
};
// @lc code=end
