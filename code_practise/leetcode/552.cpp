/*
 * [552] Student Attendance Record II
 *
 * https://leetcode.com/problems/student-attendance-record-ii/description/
 *
 * algorithms
 * Hard (31.41%)
 * Total Accepted:    6.8K
 * Total Submissions: 21.6K
 * Testcase Example:  '1'
 *
 * Given a positive integer n, return the number of all possible attendance
 * records with length n, which will be regarded as rewardable. The answer may
 * be very large, return it after mod 109 + 7.
 *
 * A student attendance record is a string that only contains the following
 * three characters:
 *
 *
 *
 * 'A' : Absent.
 * 'L' : Late.
 * ⁠'P' : Present.
 *
 *
 *
 *
 * A record is regarded as rewardable if it doesn't contain more than one 'A'
 * (absent) or more than two continuous 'L' (late).
 *
 * Example 1:
 *
 * Input: n = 2
 * Output: 8
 * Explanation:
 * There are 8 records with length 2 will be regarded as rewardable:
 * "PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
 * Only "AA" won't be regarded as rewardable owing to more than one absent
 * times.
 *
 *
 *
 * Note:
 * The value of n won't exceed 100,000.
 *
 *
 *
 *
 */
class Solution {
   using ll = int;
   const ll m = 1000000000 + 7;
   ll add(const vector<ll>& v) {
      ll ret = 0;
      for (auto a : v) {
         ret = (ret + a) % m;
      }

      return ret;
   }
public:
    int checkRecord(int n) {
       if (n == 1) {
          return 3;
       }
       vector<int> HAA {0, 2, 4}, HAP {0, 1, 4}, HAAL{0, 1, 2}, HAPL{0, 0, 1}, HALL{0, 0, 1}, NAP {0, 2, 4}, NAPL{0, 1, 2}, NALL{0, 1, 1};

       for (int i = 3; i < n; ++i) {
          HAA.push_back(add({NAP[i - 1], NAPL[i - 1], NALL[i - 1]}));
          HAP.push_back(add({HAA[i - 1], HAP[i - 1], HAAL[i - 1], HAPL[i - 1], HALL[i - 1]}));
          HAAL.push_back(add({NAP[i - 2], NAPL[i-2], NALL[i-2]}));
          HAPL.push_back(add({HAA[i - 2], HAP[i - 2], HAAL[i-2], HAPL[i-2], HALL[i-2]}));
          HALL.push_back(add({HAA[i - 2], HAP[i - 2]}));
          NAP.push_back(add({NAP[i - 1], NAPL[i - 1], NALL[i - 1]}));
          NAPL.push_back(add({NAP[i - 2], NAPL[i - 2], NALL[i - 2]}));
          NALL.push_back(add({NAP[i - 2]}));
       }

       return add({ HAA[n - 1], HAP[n - 1], HAAL[n - 1], HAPL[n - 1], HALL[n - 1], NAP[n - 1], NAPL[n - 1], NALL[n - 1]});
    }
};


/*
TESTS
1
2
3
4
5
6
7
100
1000
100000
*/
