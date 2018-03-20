/*
 * lcg 591
 *   ✔ Accepted
 *   ✔ 256/256 cases passed (9 ms)
 *   ✔ Your runtime beats 22.58 % of cpp submissions
 *
 * [591] Tag Validator
 *
 * https://leetcode.com/problems/tag-validator/description/
 *
 * algorithms
 * Hard (30.82%)
 * Total Accepted:    2.8K
 * Total Submissions: 9.3K
 * Testcase Example:  '"<DIV>This is the first line <![CDATA[<div>]]></DIV>"'
 *
 * Given a string representing a code snippet, you need to implement a tag
 * validator to parse the code and return whether it is valid. A code snippet
 * is valid if all the following rules hold:
 *
 * The code must be wrapped in a valid closed tag. Otherwise, the code is
 * invalid.
 * A closed tag (not necessarily valid) has exactly the following format :
 * <TAG_NAME>TAG_CONTENT</TAG_NAME>. Among them, <TAG_NAME> is the start tag,
 * and </TAG_NAME> is the end tag. The TAG_NAME in start and end tags should be
 * the same. A closed tag is valid if and only if the TAG_NAME and TAG_CONTENT
 * are valid.
 * A valid TAG_NAME only contain upper-case letters, and has length in range
 * [1,9]. Otherwise, the TAG_NAME is invalid.
 * A valid TAG_CONTENT may contain other valid closed tags, cdata and any
 * characters (see note1) EXCEPT unmatched <, unmatched start and end tag, and
 * unmatched or closed tags with invalid TAG_NAME. Otherwise, the TAG_CONTENT
 * is invalid.
 * A start tag is unmatched if no end tag exists with the same TAG_NAME, and
 * vice versa. However, you also need to consider the issue of unbalanced when
 * tags are nested.
 * A < is unmatched if you cannot find a subsequent >. And when you find a < or
 * </, all the subsequent characters until the next > should be parsed as
 * TAG_NAME  (not necessarily valid).
 * The cdata has the following format : <![CDATA[CDATA_CONTENT]]>. The range of
 * CDATA_CONTENT is defined as the characters between <![CDATA[ and the first
 * subsequent ]]>.
 * CDATA_CONTENT may contain any characters. The function of cdata is to forbid
 * the validator to parse CDATA_CONTENT, so even it has some characters that
 * can be parsed as tag (no matter valid or invalid), you should treat it as
 * regular characters.
 *
 *
 * Valid Code Examples:
 *
 * Input: "<DIV>This is the first line <![CDATA[<div>]]></DIV>"
 * Output: True
 * Explanation:
 * The code is wrapped in a closed tag : <DIV> and </DIV>.
 * The TAG_NAME is valid, the TAG_CONTENT consists of some characters and
 * cdata.
 * Although CDATA_CONTENT has unmatched start tag with invalid TAG_NAME, it
 * should be considered as plain text, not parsed as tag.
 * So TAG_CONTENT is valid, and then the code is valid. Thus return true.
 *
 * Input: "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"
 * Output: True
 * Explanation:
 * We first separate the code into : start_tag|tag_content|end_tag.
 * start_tag -> "<DIV>"
 * end_tag -> "</DIV>"
 * tag_content could also be separated into : text1|cdata|text2.
 * text1 -> ">>  ![cdata[]] "
 * cdata -> "<![CDATA[<div>]>]]>", where the CDATA_CONTENT is "<div>]>"
 * text2 -> "]]>>]"
 *
 * The reason why start_tag is NOT "<DIV>>>" is because of the rule 6.
 * The reason why cdata is NOT "<![CDATA[<div>]>]]>]]>" is because of the rule
 * 7.
 *
 *
 *
 * Invalid Code Examples:
 *
 * Input: "<A>  <B> </A>   </B>"
 * Output: False
 * Explanation: Unbalanced. If "<A>" is closed, then "<B>" must be unmatched,
 * and vice versa.
 *
 * Input: "<DIV>  div tag is not closed  <DIV>"
 * Output: False
 *
 * Input: "<DIV>  unmatched <  </DIV>"
 * Output: False
 *
 * Input: "<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"
 * Output: False
 *
 * Input: "<DIV> unmatched tags with invalid tag name  </1234567890> and
 * <CDATA[[]]>  </DIV>"
 * Output: False
 *
 * Input: "<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"
 * Output: False
 *
 *
 *
 * Note:
 *
 * For simplicity, you could assume the input code (including the any
 * characters mentioned above) only contain letters, digits,
 * '<','>','/','!','[',']' and ' '.
 *
 *
 */
class Solution {
    string code;
    vector<string> s;
    int i;

    void cdata () {
       // match cdata;
       const string start = "<![CDATA[";
       const string end = "]]>";
       if (i + start.size() >= code.size()) {
          throw runtime_error("cdata overflow");
       }

       for (int j = i; j < start.size(); ++j) {
          if (code[i + j] != start[j]) {
             throw runtime_error("cdata start mismatch");
          }
       }

       i = i + start.size();

       while (i + end.size() < code.size()) {
          bool matched = true;
          for (int j = 0; j < end.size(); ++j) {
             if (code[i + j] != end[j]) {
                matched = false;
                break;
             }
          }
          if (matched) {
             i = i + end.size();
             return;
          }
          i++;
       }

       throw runtime_error("cdata end mismatch");
    };

    void tag (bool footer) {
       if (i >= code.size() || code[i] != '<') {
          throw runtime_error("tag not start with <");
       }
       i++;

       if (footer) {
          if (i >= code.size() || code[i] != '/') {
             throw runtime_error("tag not start with </");
          }

          i++;
       }

       string tagName;
       while (i < code.size() && code[i] != '>') {
          if (!std::isupper(code[i])) {
             throw runtime_error("tag not upper");
          }
          tagName += code[i];
          i++;
       }

       if (i >= code.size()) {
          throw runtime_error("tag not end properly");
       }

       if (tagName.size() < 1 || tagName.size() > 9) {
          throw runtime_error("tag size");
       }

       if (footer) {
          if (s.empty() || s.back() != tagName) {
             throw runtime_error("tag stack");
          }
          s.pop_back();
       } else {
          s.push_back(tagName);
       }

       i++; // '>'
    };

    void string_literal () {
       while (i < code.size() && code[i] != '<') i++;
    };

    void tagcontent () {
       if (i + 1 >= code.size()) {
          throw runtime_error("content");
       }
       string lookahead = code.substr(i, 2);
       if (lookahead == "<!") {
          cdata();
          tagcontent();
       } else if (lookahead[0] == '<' && lookahead[1] != '/') {
          tag();
          tagcontent();
       } else if (lookahead != "</"){
          string_literal();
          tagcontent();
       } else {
          return;
       }
    };

    void tag () {
       tag(false);
       tagcontent();
       tag(true);
    };

public:
    bool isValid(string c) {
       swap(code, c);
       i = 0;

       try {
          tag();
       } catch (runtime_error &e) {
          //cout << "syntax error:" << endl;
          //cout << e.what() << endl;
          return false;
       }

       return i == code.size();
    }
};

/*
 *
*/

/*
TESTS
"<TRUE><![CDATA[wahaha]]]><![CDATA[]> wahaha]]></TRUE>"
"<DIV>This is the first line <![CDATA[<<<<<<<]]></DIV>"
"<DIV>This is the first line <![CDATA[<div>]]></DIV>"
"<A>"
"<D>This is the first line <![CDATA[<div>]]></D>"
"<DIIIIIIII>This is the first line <![CDATA[<div>]]></DIIIIIIII>"
"<>This is the first line <![CDATA[<div>]]></>"
"<DDDDDDDDDD>This is the first line <![CDATA[<div>]]></DDDDDDDDDD>"
"<A>  <B> </A>   </B>"
"<A>  <B> <CDATA[[</B>]]> </A>"
"<DIV>  div tag is not closed  <DIV>"
"<DIV>  unmatched <  </DIV>"
"<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"
"<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"
"<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"
"<DIV></DIV>"
"123456"
"<![CDATA[<div>]]>"
"<![CDATA[<div>]]><DDDDD>"
"<![CDATA[<div>]]></DDDDD>"
"</DDDDD><![CDATA[<div>]]>"
"<![CDATA[ABC]]><TAG>sometext</TAG>"
"!!!<A>123</A>"
""
"<A></A><B></B>"
*/
