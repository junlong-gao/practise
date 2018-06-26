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
    using ll = long long;
public:
    string fractionToDecimal(int numerator, int denominator) {
        ll p = abs((ll)numerator); ll q = abs((ll)denominator);
        unordered_map<ll, ll> ps;
        vector<ll> seq;
        if (p == 0) return "0"; // except p is 0... we have + or -

        string sign = ((numerator == p) ^ (denominator == q)) ? "-" : "";
        if (p >= q) {
            seq.push_back(p / q); p = p % q;
        } else {
            seq.push_back(0);
        }
        string ret = sign + to_string(seq[0]);
        while (true) {
            if (p == 0) {
                if (seq.size() > 1) ret += ".";
                for (ll i = 1; i < seq.size(); ++i) {
                    ret += to_string(seq[i]);
                }
                return ret;
            } else {
                if (ps.count(p)) {
                    if (seq.size() > 1) ret += ".";
                    ll idx = ps[p];
                    for (ll i = 1; i < idx; ++i) {
                        ret += to_string(seq[i]);
                    }
                    ret += "(";
                    for (ll i = idx; i < seq.size(); ++i) {
                        ret += to_string(seq[i]);
                    }
                    ret += ")";
                    return ret;
                } else {
                    ll d = 10 * p / q;
                    ps[p] = seq.size();
                    seq.push_back(d);
                    p = (10 * p) % q;
                }
            }
        }
        assert(0);
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
0
-5
*/
