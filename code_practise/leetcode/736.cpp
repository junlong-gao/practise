/*
   leetcode submit 736.cpp
     ✔ Accepted
     ✔ 64/64 cases passed (6 ms)
     ✔ Your runtime beats 94.85 % of cpp submissions
*/
/*
 * [736] Parse Lisp Expression
 *
 * https://leetcode.com/problems/parse-lisp-expression/description/
 *
 * algorithms
 * Hard (42.87%)
 * Total Accepted:    1.7K
 * Total Submissions: 4K
 * Testcase Example:  '"(add 1 2)"'
 *
 *
 * You are given a string expression representing a Lisp-like expression to
 * return the integer value of.
 *
 * The syntax for these expressions is given as follows.
 *
 * An expression is either an integer, a let-expression, an add-expression, a
 * mult-expression, or an assigned variable.  Expressions always evaluate to a
 * single integer.
 *
 * (An integer could be positive or negative.)
 *
 * A let-expression takes the form (let v1 e1 v2 e2 ... vn en expr), where let
 * is always the string "let", then there are 1 or more pairs of alternating
 * variables and expressions, meaning that the first variable v1 is assigned
 * the value of the expression e1, the second variable v2 is assigned the value
 * of the expression e2, and so on sequentially; and then the value of this
 * let-expression is the value of the expression expr.
 *
 * An add-expression takes the form (add e1 e2) where add is always the string
 * "add", there are always two expressions e1, e2, and this expression
 * evaluates to the addition of the evaluation of e1 and the evaluation of e2.
 *
 * A mult-expression takes the form (mult e1 e2) where mult is always the
 * string "mult", there are always two expressions e1, e2, and this expression
 * evaluates to the multiplication of the evaluation of e1 and the evaluation
 * of e2.
 *
 * For the purposes of this question, we will use a smaller subset of variable
 * names.  A variable starts with a lowercase letter, then zero or more
 * lowercase letters or digits.  Additionally for your convenience, the names
 * "add", "let", or "mult" are protected and will never be used as variable
 * names.
 *
 * Finally, there is the concept of scope.  When an expression of a variable
 * name is evaluated, within the context of that evaluation, the innermost
 * scope (in terms of parentheses) is checked first for the value of that
 * variable, and then outer scopes are checked sequentially.  It is guaranteed
 * that every expression is legal.  Please see the examples for more details on
 * scope.
 *
 *
 * Evaluation Examples:
 *
 * Input: (add 1 2)
 * Output: 3
 *
 * Input: (mult 3 (add 2 3))
 * Output: 15
 *
 * Input: (let x 2 (mult x 5))
 * Output: 10
 *
 * Input: (let x 2 (mult x (let x 3 y 4 (add x y))))
 * Output: 14
 * Explanation: In the expression (add x y), when checking for the value of the
 * variable x,
 * we check from the innermost scope to the outermost in the context of the
 * variable we are trying to evaluate.
 * Since x = 3 is found first, the value of x is 3.
 *
 * Input: (let x 3 x 2 x)
 * Output: 2
 * Explanation: Assignment in let statements is processed sequentially.
 *
 * Input: (let x 1 y 2 x (add x y) (add x y))
 * Output: 5
 * Explanation: The first (add x y) evaluates as 3, and is assigned to x.
 * The second (add x y) evaluates as 3+2 = 5.
 *
 * Input: (let x 2 (add (let x 3 (let x 4 x)) x))
 * Output: 6
 * Explanation: Even though (let x 4 x) has a deeper scope, it is outside the
 * context
 * of the final x in the add-expression.  That final x will equal 2.
 *
 * Input: (let a1 3 b2 (add a1 1) b2)
 * Output 4
 * Explanation: Variable names can contain digits after the first character.
 *
 *
 *
 * Note:
 * The given string expression is well formatted: There are no leading or
 * trailing spaces, there is only a single space separating different
 * components of the string, and no space between adjacent parentheses.  The
 * expression is guaranteed to be legal and evaluate to an integer.
 * The length of expression is at most 2000.  (It is also non-empty, as that
 * would not be a legal expression.)
 * The answer and all intermediate calculations of that answer are guaranteed
 * to fit in a 32-bit integer.
 *
 * Digestion:

s: stack for intermediate int valu
f : frames, each frame is a map from name to int
expr -> (let <push f frame> varlist expr) <pop f frame> <push s expr.val>
     |    (add expr1 expr2) <pop s v1> <pop s v2> <push s v1 + v2>
     |    (mult expr1 expr2) <pop s v1> <pop s v2> <push s v1 * v2>
     |    num_literal <push s num_literal.val>
     |    varname <push s (find varname in frame in reverse order)>

varlist -> varname expr <set f.top()[varname] <- s.back(), s.pop_back()> rest

rest    -> empty
          | varlist

varname := alphabet [alphabet | digit] *
num_literal := [+|- | empty] digit [digit]*

 */
class Solution {
   using frame = unordered_map<string, int>;
   vector<frame> scopes;
   vector<int> stack;
   int lookahead = 0;
   string buf;

   void expr();

   void varlist () {
      assert(lookahead != buf.size() && std::islower(buf[lookahead]));
      string varname;
      while (std::islower(buf[lookahead]) || std::isdigit(buf[lookahead])) {
         varname += buf[lookahead];
         lookahead++;
      }

      assert(lookahead != buf.size());
      assert(buf[lookahead] == ' ');
      lookahead++;
      assert(lookahead != buf.size());

      expr();

      assert(buf[lookahead] == ' ');
      lookahead++;
      assert(lookahead != buf.size());

      assert(!stack.empty());
      assert(!scopes.empty());
      scopes.back()[varname] = stack.back();
      stack.pop_back(); // XXX after leaving the expr scope, pop it from stack

      rest();
   }

   void rest () {
      // attempt to match a varname:
      // lower [lower] space

      int cur = lookahead;
      if (!std::islower(buf[cur])) return;
      string varname;
      while (std::islower(buf[cur]) || std::isdigit(buf[cur])) {
         varname += buf[cur];
         cur++;
      }
      if (buf[cur] != ' ') return;

      // at here, we are sure we have matched a varname
      varlist();
   }
public:
    int evaluate(string expression) {
       std::swap(expression, buf);
       expr();
       return stack.back();
    }
};

void Solution::expr() {
   if (buf[lookahead] == '(') {
      lookahead++;

      // let
      if (buf[lookahead] == 'l') {
         scopes.emplace_back();

         lookahead += 3;
         assert(buf[lookahead] == ' ');
         lookahead++;

         varlist();
         expr();

         assert(buf[lookahead] == ')');
         lookahead++;

         assert(scopes.size() != 0);
         scopes.pop_back();
      } else if (buf[lookahead] == 'a') {
      // add
         lookahead += 3;
         assert(buf[lookahead] == ' ');
         lookahead++;

         expr();
         assert(buf[lookahead] == ' ');
         lookahead++;

         expr();
         assert(buf[lookahead] == ')');
         lookahead++;

         assert(stack.size() >= 2);
         int l1 = stack.back(); stack.pop_back();
         int l2 = stack.back(); stack.pop_back();
         stack.push_back(l1 + l2);
      } else {
      // mult
         lookahead += 4;
         assert(buf[lookahead] == ' ');
         lookahead++;

         expr();
         assert(buf[lookahead] == ' ');
         lookahead++;

         expr();
         assert(buf[lookahead] == ')');
         lookahead++;

         assert(stack.size() >= 2);
         int l1 = stack.back(); stack.pop_back();
         int l2 = stack.back(); stack.pop_back();
         stack.push_back(l1 * l2);
      }
   } else {
      // num or varname
      if (std::islower(buf[lookahead])) {
         string varname;
         while (std::islower(buf[lookahead]) || std::isdigit(buf[lookahead])) {
            varname += buf[lookahead];
            lookahead++;
         }

         for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            if (it->count(varname) != 0) {
               stack.push_back(it->at(varname));
               return;
            }
         }

         assert(0);
      } else {
         // signed number
         int sign = 1;
         if (buf[lookahead] == '-') {
            sign = -1;
            lookahead++;
         } else if (buf[lookahead] == '+') {
            lookahead++;
         } else {
            assert(std::isdigit(buf[lookahead]));
         }
         string num_literal;
         while (std::isdigit(buf[lookahead])) {
            num_literal += buf[lookahead];
            lookahead++;
         }

         stack.push_back(sign * std::stoi(num_literal));
      }
   }
}

/*
 *
"(let a1 3 b2 (add a1 1) (mult b2 a1))"
"(let a 1 (let b 2 (let c 3 a)))"
"(let x 1 x)"
"(mult -1 -2)"
"(add 1 -2)"
"(mult -1 -2)"
"(let x 1 x)"
"(add (let x 1 x) -2)"
"(let a 1 (let b 2 3))"
"(let a1 3 b2 (add a1 1) x (mult b2 a1) (add x b2))"
"(add 1 2)"
"(mult 3 (add 2 3))"
"(let x 2 (mult x 5))"
"(let x 3 x 2 x)"
"(let x 1 y 2 x (add x y) (add x y))"
"(let x 2 (add (let x 3 (let x 4 x)) x))"
"(let a1 3 b2 (add a1 1) b2)"
"(let x 2 (mult x (let x 3 y 4 (add x y))))"
"(mult 3 (add 2 3))"
"(let x 2 (mult x 5))"
"(let x 3 x 2 x)"
"(let x 1 y 2 x (add x y) (add x y))"
"(let x 2 (add (let x 3 (let x 4 x)) x))"
"(let a1 3 b2 (add a1 1) b2)"
"(let a1 3 b2 (add a1 1) (mult b2 a1))"
"(let a 1 (let b 2 (let c 3 a)))"
"(let x 1 x)"
"(mult -1 -2)"
"(add 1 -2)"
"(mult -1 -2)"
"(let x 1 x)"
"(add (let x 1 x) -2)"
"(let a 1 (let b 2 3))"
"(let a1 3 b2 (add a1 1) x (mult b2 a1) (add x b2))"
"(add 1 2)"
 */
/*
TESTS
"(let x 2 (mult x (let x 3 y 4 (add x y))))"
"(mult 3 (add 2 3))"
"(let x 2 (mult x 5))"
"(let x 3 x 2 x)"
"(let x 1 y 2 x (add x y) (add x y))"
"(let x 2 (add (let x 3 (let x 4 x)) x))"
"(let a1 3 b2 (add a1 1) b2)"
"(let a1 3 b2 (add a1 1) (mult b2 a1))"
"(let a 1 (let b 2 (let c 3 a)))"
"(let x 1 x)"
"(mult -1 -2)"
"(add 1 -2)"
"(mult -1 -2)"
"(let x 1 x)"
"(add (let x 1 x) -2)"
"(let a 1 (let b 2 3))"
"(let a1 3 b2 (add a1 1) x (mult b2 a1) (add x b2))"
"(add 1 2)"
*/
