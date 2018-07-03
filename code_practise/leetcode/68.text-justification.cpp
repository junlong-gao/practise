
/*
 * [68] Text Justification
 *
 * https://leetcode.com/problems/text-justification/description/
 *
 * algorithms
 * Hard (20.44%)
 * Total Accepted:    73.3K
 * Total Submissions: 358.6K
 * Testcase Example:  '["This", "is", "an", "example", "of", "text", "justification."]\n16'
 *
 * Given an array of words and a width maxWidth, format the text such that each
 * line has exactly maxWidth characters and is fully (left and right)
 * justified.
 *
 * You should pack your words in a greedy approach; that is, pack as many words
 * as you can in each line. Pad extra spaces ' ' when necessary so that each
 * line has exactly maxWidth characters.
 *
 * Extra spaces between words should be distributed as evenly as possible. If
 * the number of spaces on a line do not divide evenly between words, the empty
 * slots on the left will be assigned more spaces than the slots on the right.
 *
 * For the last line of text, it should be left justified and no extra space is
 * inserted between words.
 *
 * Note:
 *
 *
 * A word is defined as a character sequence consisting of non-space characters
 * only.
 * Each word's length is guaranteed to be greater than 0 and not exceed
 * maxWidth.
 * The input array words contains at least one word.
 *
 *
 * Example 1:
 *
 *
 * Input:
 * words = ["This", "is", "an", "example", "of", "text", "justification."]
 * maxWidth = 16
 * Output:
 * [
 * "This    is    an",
 * "example  of text",
 * "justification.  "
 * ]
 *
 *
 * Example 2:
 *
 *
 * Input:
 * words = ["What","must","be","acknowledgment","shall","be"]
 * maxWidth = 16
 * Output:
 * [
 * "What   must   be",
 * "acknowledgment  ",
 * "shall be        "
 * ]
 * Explanation: Note that the last line is "shall be    " instead of "shall
 * be",
 * because the last line must be left-justified instead of fully-justified.
 * ⁠            Note that the second line is also left-justified becase it
 * contains only one word.
 *
 *
 * Example 3:
 *
 *
 * Input:
 * words =
 * ["Science","is","what","we","understand","well","enough","to","explain",
 * "to","a","computer.","Art","is","everything","else","we","do"]
 * maxWidth = 20
 * Output:
 * [
 * "Science  is  what we",
 * ⁠ "understand      well",
 * "enough to explain to",
 * "a  computer.  Art is",
 * "everything  else  we",
 * "do                  "
 * ]
 *
 *
 */
class Solution {
    /*
     *
     * track total number of char used
     *
     *  while there is word left
     *   if we can put it with space into the current line
     *     put it
     *   else
     *     if we can put it without space
     *       put it
     *     break
     *
     * remainSpace = L - total word char count
     * k = number of words
     * if (this is the last line or k == 1) {
     *    place first k - 1 words with space
     *    place the last without space
     *    put remain spaces to the reset of the line
     * } else {
     *    spacePerBucket = remainSpace / (k - 1)
     *    for the first k - 1 words
     *       put spacePerBucket
     *       if it is first remainSpace % (k - 1)
     *         put one more space
     * }
     *
     * return this line
     */
    string lineHandler(int &curIdx, const vector<string> &words, int L) {
       string ret;
       int totalChar = 0, totalWordChar = 0, oldIdx = curIdx;

       while (curIdx < words.size()) {
          if (words[curIdx].length() + totalChar <= L) {
             if (words[curIdx].length() + totalChar + 1 <= L) {
                totalChar++;
             }
             totalChar += words[curIdx].length();
             totalWordChar += words[curIdx].length();
             curIdx++;
          } else {
             break;
          }
       }

       int remainSpace = L - totalWordChar;
       int k = curIdx - oldIdx;

       assert(k > 0);
       if (curIdx == words.size() || k == 1) {
          // left justified
          for (int i = oldIdx; i < curIdx - 1; ++i) {
             ret += words[i];
             ret += " ";
             remainSpace--;
          }

          ret += words[curIdx - 1];
          ret += string(remainSpace, ' ');
       } else {
          // center justified
          int ss = remainSpace / (k - 1);
          for (int i = oldIdx; i < curIdx - 1; ++i) {
             ret += words[i];
             ret += string(ss, ' ');

             if ((i - oldIdx) < remainSpace % (k - 1)) {
                ret += " ";
             }
          }

          ret += words[curIdx - 1];
       }

       //cout << ret << endl;
       assert(ret.length() == L);
       return ret;
    }
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ret;
        int i = 0;
        while (i < words.size()) {
           ret.emplace_back(lineHandler(i, words, maxWidth));
        }

        return ret;
    }
};

