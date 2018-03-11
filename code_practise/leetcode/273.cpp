/*
 * leetcode submit 273.cpp
  ✔ Accepted
  ✔ 601/601 cases passed (8 ms)
  ✔ Your runtime beats 1.88 % of cpp submissions
 */
/*
 * [273] Integer to English Words
 *
 * https://leetcode.com/problems/integer-to-english-words/description/
 *
 * algorithms
 * Hard (22.72%)
 * Total Accepted:    55.8K
 * Total Submissions: 245.7K
 * Testcase Example:  '123'
 *
 * 
 * Convert a non-negative integer to its english words representation. Given
 * input is guaranteed to be less than 231 - 1.
 * 
 * 
 * For example,
 * 
 * 123 -> "One Hundred Twenty Three"
 * 12345 -> "Twelve Thousand Three Hundred Forty Five"
 * 1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
 * Seven"
 */
class Solution {
   const vector<string> digits {
      "",
      "One",
      "Two",
      "Three",
      "Four",
      "Five",
      "Six",
      "Seven",
      "Eight",
      "Nine",
   };

   const vector<string> tens {
      "",
      "",
      "Twenty",
      "Thirty",
      "Forty",
      "Fifty",
      "Sixty",
      "Seventy",
      "Eighty",
      "Ninety"
   };

   const vector<string> ele {
      "Ten",
      "Eleven",
      "Twelve",
      "Thirteen",
      "Fourteen",
      "Fifteen",
      "Sixteen",
      "Seventeen",
      "Eighteen",
      "Nineteen"
   };

   const vector<string> ks {
      "",
      "Thousand",
      "Million",
      "Billion"
   };
   // high [idx + 2] [idx + 1] [idx] low
   vector<string> printHun(vector<int> &tokens, int idx) {
      vector<string> ret;
      if (tokens[idx + 2] != 0) {
         ret.push_back(digits[tokens[idx+2]]);
         ret.push_back("Hundred");
      }

      if (tokens[idx + 1] != 1) {
         ret.push_back(tens[tokens[idx + 1]]);
         ret.push_back(digits[tokens[idx]]);
      } else {
         ret.push_back(ele[tokens[idx]]);
      }

      return ret;
   }
public:
    string numberToWords(int num) {
       vector<int> tokens(13, 0);
       string rst;
       int i = 0;
       while (num > 0) {
          tokens[i++] = num % 10;
          num = num / 10;
       }

       auto ret = printHun(tokens, 0);

       for (int i : {9, 6, 3, 0}) {
          string t;
          ret = printHun(tokens, i);
          for (int i = 0; i < ret.size(); ++i) {
             if (ret[i].empty()) continue;
             if (!t.empty()) t += " ";
             t += ret[i];
          }

          if (t.empty()) continue;
          if (!rst.empty()) rst += " ";
          rst += t;
          if (!ks[i / 3].empty()) rst += " ";  // <---XXX
          rst += ks[i / 3];
       }

       return rst.empty()? "Zero" : rst;
    }
};


/*
TESTS
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
30
40
50
60
70
80
90
100
112
120
123
1000
1001
1100
1010
1110
1011
987654
99999999
1009999999
1000000000
1000000
1000
2119999999
*/
