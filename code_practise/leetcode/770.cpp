/*
 * > leetcode submit 770.cpp
 *   ✔ Accepted
 *     158/158 cases passed (14 ms)
 *     Your runtime beats 49.18 % of cpp submissions
 */
/*
 * [781] Basic Calculator IV
 *
 * https://leetcode.com/problems/basic-calculator-iv/description/
 *
 * algorithms
 * Hard (42.89%)
 * Total Accepted:    552
 * Total Submissions: 1.3K
 * Testcase Example:  '"e + 8 - a + 5"\n["e"]\n[1]'
 *
 * Given an expression such as expression = "e + 8 - a + 5" and an evaluation
 * map such as {"e": 1} (given in terms of evalvars = ["e"] and evalints =
 * [1]), return a list of tokens representing the simplified expression, such
 * as ["-1*a","14"]
 *
 *
 * An expression alternates chunks and symbols, with a space separating each
 * chunk and symbol.
 * A chunk is either an expression in parentheses, a variable, or a
 * non-negative integer.
 * A variable is a string of lowercase letters (not including digits.) Note
 * that variables can be multiple letters, and note that variables never have a
 * leading coefficient or unary operator like "2x" or "-x".
 *
 *
 * Expressions are evaluated in the usual order: brackets first, then
 * multiplication, then addition and subtraction. For example, expression = "1
 * + 2 * 3" has an answer of ["7"].
 *
 * The format of the output is as follows:
 *
 *
 * For each term of free variables with non-zero coefficient, we write the free
 * variables within a term in sorted order lexicographically. For example, we
 * would never write a term like "b*a*c", only "a*b*c".
 * Terms have degree equal to the number of free variables being multiplied,
 * counting multiplicity. (For example, "a*a*b*c" has degree 4.) We write the
 * largest degree terms of our answer first, breaking ties by lexicographic
 * order ignoring the leading coefficient of the term.
 * The leading coefficient of the term is placed directly to the left with an
 * asterisk separating it from the variables (if they exist.)  A leading
 * coefficient of 1 is still printed.
 * An example of a well formatted answer is ["-2*a*a*a", "3*a*a*b", "3*b*b",
 * "4*a", "5*c", "-6"] 
 * Terms (including constant terms) with coefficient 0 are not included.  For
 * example, an expression of "0" has an output of [].
 *
 *
 * Examples:
 *
 *
 * Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
 * Output: ["-1*a","14"]
 *
 * Input: expression = "e - 8 + temperature - pressure",
 * evalvars = ["e", "temperature"], evalints = [1, 12]
 * Output: ["-1*pressure","5"]
 *
 * Input: expression = "(e + 8) * (e - 8)", evalvars = [], evalints = []
 * Output: ["1*e*e","-64"]
 *
 * Input: expression = "7 - 7", evalvars = [], evalints = []
 * Output: []
 *
 * Input: expression = "a * b * c + b * a * c * 4", evalvars = [], evalints =
 * []
 * Output: ["5*a*b*c"]
 *
 * Input: expression = "((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c
 * - a))",
 * evalvars = [], evalints = []
 * Output:
 * ["-1*a*a*b*b","2*a*a*b*c","-1*a*a*c*c","1*a*b*b*b","-1*a*b*b*c","-1*a*b*c*c","1*a*c*c*c","-1*b*b*b*c","2*b*b*c*c","-1*b*c*c*c","2*a*a*b","-2*a*a*c","-2*a*b*b","2*a*c*c","1*b*b*b","-1*b*b*c","1*b*c*c","-1*c*c*c","-1*a*a","1*a*b","1*a*c","-1*b*c"]
 *
 *
 * Note:
 *
 *
 * expression will have length in range [1, 250].
 * evalvars, evalints will have equal lengths in range [0, 100].
 *
 *
 * Digestion:
 * Lexing
 *   number is a sequence of digits until the first space or ')'
 *   var is a sequence of lower case until the first space or ')'
 *
 * Parsing (two level precedence):
 * expr -> term restTerms
 *
 * restTerms -> + term { push [(+, 0)] } restTerms
 *           |  - term { push [(-, 0)] } restTerms
 *           |  none
 *
 * term -> factor restFactors
 *
 * restFactors -> * factor { push [(*, 0)]} restFactors
 *             |  / factor { push [(/, 0)]} restFactors
 *             | none
 *
 * factor -> number  { push [("", number)] }
 *        |  var     { push [(var, 1)] or [("", evalints[val])] depending on val in evalvars}
 *        | ( expr )
 *
 * Translation:
 * Eval the suffix representation, where op is '+', '-', '*', '\'
 * and the oprand is a map from var name to its coefficient.
 * oprand1 + or - oprand2 = combine coefficent with + or -
 * oprand1 * oprand2 = for each var in oprand1, compute coefficient op1 * op2
 *                     and produce new var =  concat var1var2 and sort by var1 and var2
 *                     and combine all results together
 * combine will drop var with coe 0
 * oprand1 / oprand2 = does not seem to work with var?
 *                     not in test case
 */
class Solution {
   string in;
   int lookahead;
   vector<pair<string, int>> tokens;
   unordered_map<string, int> consts;
   void expr();

   void factor() {
      if (lookahead == in.size()) assert(0);

      int cur = lookahead;
      if (std::isdigit(in[lookahead])) {
         // parse number
         while (lookahead < in.size() && std::isdigit(in[lookahead])) {
            lookahead++;
         }

         if (lookahead == cur) return;

         tokens.push_back({"", std::stoi(in.substr(cur, lookahead - cur))});
      } else if (in[lookahead] != '(') {
         // parse var
         while (lookahead < in.size() && std::islower(in[lookahead])) {
            lookahead++;
         }

         if (lookahead == cur) return;

         string var = in.substr(cur, lookahead - cur);

         if (consts.count(var) != 0) {
            tokens.push_back({"", consts.at(var)});
         } else { tokens.push_back({var, 1}); }


      } else {
         // parse expr
         assert(in[lookahead] == '('); lookahead++;
         expr();
         assert(in[lookahead] == ')'); lookahead++;
      }

      if (lookahead < in.size() && in[lookahead] == ' ') lookahead++;
   }

   void restFactors() {
      if (lookahead == in.size() || (in[lookahead] != '*' && in[lookahead] != '/')) return; // XXX

      string op {in[lookahead]};
      lookahead++;
      assert(in[lookahead] == ' ');
      lookahead++;

      factor();

      tokens.push_back({op, 0});

      restFactors();
   }

   void term() {
      if (lookahead == in.size()) assert(0);

      factor();
      restFactors();
   }

   void restTerms() {
      if (lookahead == in.size() || (in[lookahead] != '+' && in[lookahead] != '-')) return; // XXX

      assert(in[lookahead] == '+' || in[lookahead] == '-');
      string op {in[lookahead]};
      lookahead++;
      assert(in[lookahead] == ' ');
      lookahead++;

      term();

      tokens.push_back({op, 0});

      restTerms();
   }

   vector<string> eval() {
      auto c = [&](const vector<string> &l, const vector<string> &r) {
         if (l.size() != r.size()) {
            return r.size() < l.size();
         }

         for (int i = 0; i < l.size(); ++i) {
            if (l[i] != r[i]) return l[i] < r[i];
         }

         return false;
      };

      auto sanitize = [&](map<vector<string>, int, decltype(c)> & first) {
         map<vector<string>, int, decltype(c)> toPush(c);
         for (const auto & factor : first) {
            if (factor.second == 0) { continue; }
            vector<string> symbol;
            for (const auto & varName : factor.first) {
               if (varName.size() == 0) {continue;}
               symbol.push_back(varName);
            }

            toPush[symbol] = factor.second;
         }

         return toPush;
      };

      vector<map<vector<string>, int, decltype(c)>> s;
      for (const auto &term : tokens) {
         if (term.first == "+") {
            auto second = s.back(); s.pop_back();
            auto first = s.back(); s.pop_back();
            for (const auto &factor : second) {
               first[{factor.first}] += factor.second;
            }

            s.push_back(sanitize(first));
         } else if (term.first == "-") {
            auto second = s.back(); s.pop_back();
            auto first = s.back(); s.pop_back();
            for (const auto &factor : second) {
               first[{factor.first}] -= factor.second;
            }

            s.push_back(sanitize(first));
         } else if (term.first == "*") {
            auto second = s.back(); s.pop_back();
            auto first = s.back(); s.pop_back();
            map<vector<string>, int, decltype(c)> prod(c);
            for (const auto & x : first) { for (const auto & y : second) {
               vector<string> var = x.first;
               var.insert(var.end(), y.first.begin(), y.first.end());
               sort(var.begin(), var.end());
               int val = x.second * y.second;
               prod[var] += val;
            }}

            s.push_back(sanitize(prod));
         } else {
            map<vector<string>, int, decltype(c)> single(c);

            vector<string> t;
            if (term.first.size() > 0) {
               t.push_back(term.first);
            }
            single[t] = term.second;  // XXX not single[{term.first}]
            s.push_back(single);
         }
      }

      assert(s.size() == 1);
      vector<string> ret;
      for (const auto & term : s.back()) {
         if (term.second == 0) continue;
         string symbol;
         for (const auto & var : term.first) {
            if (var.size() == 0) continue;
            symbol += "*";
            symbol += var;
         }
         ret.push_back(std::to_string(term.second) + symbol);
      }

      return ret;
   }
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
       lookahead = 0;
       std::swap(in, expression);
       for (int i = 0; i < evalvars.size(); ++i) {
          consts[evalvars[i]] = evalints[i];
       }

       expr();
       assert(lookahead == in.size());

       return eval();
    }
};

void Solution::expr() {

   if (lookahead == in.size()) return;

   term();
   restTerms();
}

/*
"(e + 8) * (e - 8)"
[]
[]
"abc + cba"
[]
[]
 */

/*
TESTS
"e - 8 + temperature - pressure"
["e", "temperature"]
[1, 12]
"(e + 8) * (e - 8)"
[]
[]
"abc + cba"
[]
[]
"((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))"
[]
[]
"((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))"
["a", "b", "c"]
[0, 1, 2]
"((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))"
["a", "b"]
[0, 1]
"((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))"
["a"]
[0]
*/
