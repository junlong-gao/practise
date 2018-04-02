/*
> leetcode submit 65.cpp

  ✔ Accepted
  ✔ 1481/1481 cases passed (13 ms)
  ✔ Your runtime beats 6.65 % of cpp submissions
*/

/*
 * [65] Valid Number
 *
 * https://leetcode.com/problems/valid-number/description/
 *
 * algorithms
 * Hard (12.94%)
 * Total Accepted:    82.2K
 * Total Submissions: 634.9K
 * Testcase Example:  '"3"'
 *
 * Validate if a given string is numeric.
 *
 *
 * Some examples:
 * "0" => true
 * "   0.1  " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 *
 *
 * Note: It is intended for the problem statement to be ambiguous. You should
 * gather all requirements up front before implementing one.
 *
 *
 *
 * Update (2015-02-10):
 * The signature of the C++ function had been updated. If you still see your
 * function signature accepts a const char * argument, please click the reload
 * button  to reset your code definition.
 *
 * Digestion:
 * More examples:
 * "0123"     -> true
 * "0. 1"     -> false
 * "-0.1"     -> true
 * "+0.1"     -> true
 * "0.1e10"   -> true
 * "0.1e10.1" -> false
 * "3."       -> true
 * ".3"       -> true
 * "10.e10"   -> true
 *
 * Lexical Analysis.
 * Regular Definition:
 * digit    -> 0|1| ... |9
 * digits   -> digit digit*
 * body     -> digits | digits.(digits|eps) | .digits
 * optSign  -> (+|-) | eps
 * optExp   -> (e optSign digits) | eps
 * optSpace ->  *
 * number   -> optSpace optSign digits optFrac optExp optSpace
 *
 */
class Solution {
public:
    bool isNumber(string s) {
       static const regex p{[&]() -> string {
         string digit      {"[0123456789]"},
                digits     {digit + digit + "*"},
                body       {"((" + digits + ")|(" + digits + "[.]" + "(" + digits + ")?" + ")|(" + "[.]" + digits + "))"},
                optSign    {"[+-]?"},
                optExp     {"(e"+ optSign  + digits + ")?"},
                optSpace   {"[ ]*"};
          //cout << optSpace + optSign + body + optExp + optSpace << endl;
          return optSpace + optSign + body + optExp + optSpace;
       }()};

       return regex_match(s, p);
    }
};


/*
TESTS
"0. 1"
"-0.1"
"+0.1"
"0.1e10"
"0.1e10.1"
"0123"
"1 "
".1"
".1e10"
"e10"
"3."
"10.e10"
*/
