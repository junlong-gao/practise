/*
 * 40:06
 > leetcode submit 726.cpp
  ✔ Accepted
  ✔ 28/28 cases passed (3 ms)
  ✔ Your runtime beats 11.02 % of cpp submissions
 */
class Solution {
    unordered_map<string, int> s;
    vector<string> tokens;
    void formula(int start, int end, int count) {
       int i = start, last = i;
       while (i < end) {
          //cout << tokens[i] << endl;
          if (tokens[i] == "(") {
             int newcount = count;
             int compondEnd = i;
             int match = 0;     // <------- remember to match the outmost ")"
             while (i < end) {  // <------- this can be faster using single scan
                if (tokens[i] == "(") {
                   match++;
                } else if (tokens[i] == ")") {
                   match--;
                }

                if (match == 0) {
                   break;
                }

                i++;
                compondEnd++;
             }

             if (i + 1 < end && std::isdigit(tokens[i+1][0])) {
                newcount *= std::stoi(tokens[i+1]);
                i++;
             }

             formula(last + 1, compondEnd, newcount);
          } else {
             int newcount = count;
             if (i + 1 < end && std::isdigit(tokens[i+1][0])) {
                newcount *= std::stoi(tokens[i+1]);
                i++;
             }

             s[tokens[last]] += newcount;
          }

          i++;
          last = i;
       }
    }

public:
    string countOfAtoms(string f) {
       int i = 0;
       while (i < f.size()) {
          if (std::isdigit(f[i])) {
             tokens.emplace_back();
             while (i < f.size() && std::isdigit(f[i])) {
                tokens.back() += f[i];
                i++;
             }
          } else if (f[i] == '(') {
             tokens.push_back("(");
             i++;
          } else if (f[i] == ')') {
             tokens.push_back(")");
             i++;
          } else {
             assert(std::isupper(f[i]));
             tokens.emplace_back();
             tokens.back() += f[i]; i++;
             while (i < f.size() && std::islower(f[i])) {
                tokens.back() += f[i];
                i++;
             }
          }
       }

       formula(0, tokens.size(), 1);
       map<string, int> output(s.begin(), s.end());
       string ret;
       for (const auto &pr : output) {
          ret += pr.first;
          if (pr.second > 1) {
             ret += std::to_string(pr.second);
          }
       }

       return ret;
    }
};

/*
 *
*/

/*
TESTS
"K4(ON(SO3)2)2"
"H2O"
"Mg(OH)2"
"Ca(OH2O)"
"Ca(O(H2O)4)"
*/
