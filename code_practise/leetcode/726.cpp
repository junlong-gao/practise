/*
 * 40:06
 > leetcode submit 726.cpp
  ✔ Accepted
  ✔ 28/28 cases passed (3 ms)
  ✔ Your runtime beats 11.02 % of cpp submissions
 */
class Solution {
    unordered_map<string, int> bag;
    vector<string> tokens;
    vector<int> semanticStack;
    int idx = 0;

    void match() {
       idx--;
    }

    void formula() {
       idx = tokens.size() - 1;
       semanticStack.push_back(1);
       while (idx >= 0) {
          if (tokens[idx] == "(") {
             semanticStack.pop_back();
             match();
             continue;
          }

          int newcount = semanticStack.back();
          if (std::isdigit(tokens[idx][0])) {
             newcount *= std::stoi(tokens[idx]);
             match();
          }

          if (tokens[idx] == ")") {
             semanticStack.push_back(newcount);
             match();
          } else {
             bag[tokens[idx]] += newcount;
             match();
          }
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

       formula();
       map<string, int> output(bag.begin(), bag.end());
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
TESTS
"K4(ON(SO3)2)2"
"H2O"
"Mg(OH)2"
"Ca(OH2O)"
"Ca(O(H2O)4)"
*/
