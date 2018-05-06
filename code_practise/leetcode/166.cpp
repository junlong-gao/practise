/*
 * [166] Fraction to Recurring Decimal
 *
 * https://leetcode.com/problems/fraction-to-recurring-decimal/description/
 *
 * algorithms
 * Medium (18.16%)
 * Total Accepted:    64.7K
 * Total Submissions: 356.5K
 * Testcase Example:  '1\n2'
 *
 * Given two integers representing the numerator and denominator of a fraction,
 * return the fraction in string format.
 * 
 * If the fractional part is repeating, enclose the repeating part in
 * parentheses.
 * 
 * Example 1:
 * 
 * 
 * Input: numerator = 1, denominator = 2
 * Output: "0.5"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: numerator = 2, denominator = 1
 * Output: "2"
 * 
 * Example 3:
 * 
 * 
 * Input: numerator = 2, denominator = 3
 * Output: "0.(6)"
 * 
 * 
 * Digestion:
 * Cute math:
 * to find the first digit of t / d
 * t / d = d_1 * 10^{-1} + d_2 * 10^{-2} ...
 * t * 10 = d * d_1 + d * d_2 * 10^{-1} ...
 *
 * so first digit = floor(t * 10 / d) = d_1
 *
 * t * 10 % d := t * 10 - floor(t * 10 / d) * d = d * d_2 * 10^{-1} ...
 *
 * then, let t' = t * 10 % d, d' = d
 * thus the first digit of t' / d' is the second digit of t / d, repeat until t is 0
 * (then all follows 0)
 * 
 * if you have already seen t / d , this is the beginning of the repeat pattern
 */
class Solution {
public:
    string fractionToDecimal(long long numerator, long long denominator) {
       string sign = "";
       if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0)) {
          sign = "-";
       }

       numerator = abs(numerator);
       denominator = abs(denominator);

       long long lead = numerator / denominator;
       long long t = numerator % denominator, d = denominator;
       vector<int> digit;
       unordered_map<long long, int> tmap;
       int repeat = -1;

       while (t != 0) {
          if (tmap.count(t) != 0) {
             repeat = tmap[t];
             break;
          }

          tmap[t] = digit.size();
          digit.emplace_back(t * 10 / d); // t * 10 can overflow, consider 1 / INT_MAX(32bit)
          t = (t * 10) % d;
       }

       // format the result:
       string ret = sign + to_string(lead);
       if (digit.empty()) return ret;
       ret += ".";
       if (repeat == -1) {
         repeat = digit.size();
       }
       for (int i = 0; i < repeat; ++i) {
          ret += to_string(digit[i]);
       }
       if (repeat == digit.size()) return ret;
       ret += "(";
       for (int i = repeat; i < digit.size(); ++i) {
          ret += to_string(digit[i]);
       }
       ret += ")";
       return ret;
    }
};


/*
 */

/*
TESTS
1
2
2
8
8
2
7
21
70
21
7
11
40
11
22
7
22
700
1
-1
7
-12
-1
-2147483648
1
99
1
90
11
90
*/
