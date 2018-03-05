/*
 * > leetcode submit 679.cpp
 *   ✔ Accepted
 *     70/70 cases passed (21 ms)
 *     Your runtime beats 9.16 % of cpp submissions
 * 
 * [679] 24 Game
 *
 * https://leetcode.com/problems/24-game/description/
 *
 * algorithms
 * Hard (38.66%)
 * Total Accepted:    6.3K
 * Total Submissions: 16.3K
 * Testcase Example:  '[4,1,8,7]'
 *
 * 
 * You have 4 cards each containing a number from 1 to 9.  You need to judge
 * whether they could operated through *, /, +, -, (, ) to get the value of
 * 24.
 * 
 * 
 * Example 1:
 * 
 * Input: [4, 1, 8, 7]
 * Output: True
 * Explanation: (8-4) * (7-1) = 24
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: [1, 2, 1, 2]
 * Output: False
 * 
 * 
 * 
 * Note:
 * 
 * The division operator / represents real division, not integer division.  For
 * example, 4 / (1 - 2/3) = 12.
 * Every operation done is between two numbers.  In particular, we cannot use -
 * as a unary operator.  For example, with [1, 1, 1, 1] as input, the
 * expression -1 - 1 - 1 - 1 is not allowed.
 * You cannot concatenate numbers together.  For example, if the input is [1,
 * 2, 1, 2], we cannot write this as 12 + 12.
 * 
 * 
 */
class Solution {
   const double target = 24.0;
   const double delta = 1000 * std::numeric_limits<double>::epsilon(); // XXX test case 8 3 8 3
   bool eval(int idx, const vector<bool> &isOp, vector<int> &nums, vector<char> &e) {
      if (idx == isOp.size()) {
         string str(e.begin(), e.end());
         vector<double> s;
         for (int i = 0; i < e.size(); ++i) {
            if (e[i] == '+') {
               double op2 = s.back(); s.pop_back();
               double op1 = s.back(); s.pop_back();
               s.push_back(op1 + op2);
            } else if (e[i] == '*') {
               double op2 = s.back(); s.pop_back();
               double op1 = s.back(); s.pop_back();
               s.push_back(op1 * op2);
            } else if (e[i] == '-') {
               double op2 = s.back(); s.pop_back();
               double op1 = s.back(); s.pop_back();
               s.push_back(op1 - op2);
            } else if (e[i] == '/') {
               double op2 = s.back(); s.pop_back();
               double op1 = s.back(); s.pop_back();
               if (std::abs(op2) <= std::numeric_limits<double>::epsilon()) {
                  return false;
               }
               s.push_back(op1 / op2);
            } else {
               int v = e[i] - '0';
               s.push_back(v);
            }
         }

         //cout << "eval:" << str <<"="<< s.back() << " delta=" << std::abs(s.back() - target) << " e=" << std::numeric_limits<double>::epsilon()<< endl;
         return std::abs(s.back() - target) <= delta ;
      }

      // search
      if (isOp[idx]) {
         for (char c : {'*', '-', '+', '/'}) {
            e.push_back(c);
            bool ret = eval(idx + 1, isOp, nums, e);
            if (ret) {
               return true;
            }
            e.pop_back();
         }
      } else {
         for (int i = 1; i < 10; ++i) {
            if (nums[i] == 0) continue;
            nums[i]--;
            e.push_back(i + '0');
            bool ret = eval(idx + 1, isOp, nums, e);
            if (ret) {
               return true;
            }
            e.pop_back();
            nums[i]++;
         }
      }

      return false;
   }
public:
    bool judgePoint24(vector<int>& nums) {
       vector<int> mask(10, 0);
       for (int i = 0; i < nums.size(); ++i) {
          mask[nums[i]]++;
       }

       vector<char> bag;
       if (eval(0, {false, false, true, false, false, true, true}, mask, bag)) return true;
       if (eval(0, {false, false, true, false, true, false, true}, mask, bag)) return true;
       if (eval(0, {false, false, false, false, true, true, true}, mask, bag)) return true;

       return false;
    }
};

/*
 *
*/

/*
TESTS
[1,5,9,1]
[4, 1, 8, 7]
[1, 2, 1, 2]
[3,3,8,8]
*/
