/*
 * > lcg 466
 *   ✔ Accepted
 *     41/41 cases passed (183 ms)
 *     Your runtime beats 19.79 % of cpp submissions
 *
 * [466] Count The Repetitions
 *
 * https://leetcode.com/problems/count-the-repetitions/description/
 *
 * algorithms
 * Hard (27.27%)
 * Total Accepted:    5.4K
 * Total Submissions: 19.9K
 * Testcase Example:  '"acb"\n4\n"ab"\n2'
 *
 * Define S = [s,n] as the string S which consists of n connected strings s.
 * For example, ["abc", 3] ="abcabcabc".
 * On the other hand, we define that string s1 can be obtained from string s2
 * if we can remove some characters from s2 such that it becomes s1. For
 * example, “abc”  can be obtained from “abdbec” based on our definition, but
 * it can not be obtained from “acbbe”.
 * You are given two non-empty strings s1 and s2 (each at most 100 characters
 * long) and two integers 0 ≤ n1 ≤ 106 and 1 ≤ n2 ≤ 106. Now consider the
 * strings S1 and S2, where S1=[s1,n1] and S2=[s2,n2]. Find the maximum integer
 * M such that [S2,M] can be obtained from S1.
 *
 * Example:
 *
 * Input:
 * s1="acb", n1=4
 * s2="ab", n2=2
 *
 * Return:
 * 2
 *
 *
 * Digestion:
 * The goal is to count how many times [s2, n2] appears in [s1, n1].
 * We know how to find the maximal length of substring s2 in s1. The question
 * is how to do that for [s1, n1] and [s2, n2].
 *
 * Start simple:
 * s1 = abacb, n1 = 8
 * s2 = bcaa,  n2 = 2
 *
 *   a b a c b | a b a c b | a b a c b | a b a c b | a b a c b | a b a c b | a b a c b | a b a c b
 *
 *      0  1     2   3   0         1     2   3   0         1     2   3   0         1     2   3
 *
 * d           2           3           1           3           1           3           1           2
 * x           2           5           6           9          10          13          14          16
 *
 * 16 / 4 = 4
 *
 * We see that s2 appears 4 times in [s1, n1], so we conclude that M = 2.
 *
 * The question is how to find 4 quickly.
 *
 * A naive way is to use s2 to match [s1, n1], takes |s1||s2|n1, slow.
 *
 * A smart way can reduce the complexity to n1, which makes the time complexity manageable.
 *
 * The trick is as follows: for each s1, everytime we are trying to match it with
 * s2 from an offset: first start 0, then start 2, then 1 ...
 * If we know given an offset k, we can immediately answer a single s1 matches
 * d char with s2s2s2...  offset by k, and we have matched x char of s2
 * sofar,then the next repeated s1 we will be looking for matching s2 with
 * offset (x + d) % |s2|.
 *
 * To use this fact, we just need to compute this table: for each offset of s2,
 * we calculate how long s2s2s2s2... matches s1, and store it.
 * Then we go through this table, maintain the total length matched in s2s2s2s2...
 * Finally report this total length / n2 / |s2|
 *
 * There is a better way of doing this by exploiting the fact that d is by nature
 * periodic.
 */
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
       int n = s2.size();
       vector<int> d(n, 0);
       for (int i = 0; i < n; ++i) {
          int j = i;
          for (int k = 0; k < s1.size(); ++k) {
             if (s2[j % n] == s1[k]) {
                j++;
             }
          }
          d[i] = j - i;
       }

       int totalMatched = 0;
       for (int i = 0; i < n1; ++i) {
          totalMatched += d[totalMatched % n];
       }

       return totalMatched / s2.size() / n2;
    }
};


/*
TESTS
"acb"
4
"ab"
2
"acb"
4
"aeb"
2
"acb"
4
"ab"
3
"lovenicoloveliveniconiconiconiniconjcoaaajo"
201641
"lovenanjo"
401
*/
