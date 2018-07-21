#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(string &S) {
    // write your code in C++14 (g++ 6.2.0)
    vector<int> m;
    static const int maxV = (1 << 20) - 1;
    int i = 0;
    while (i < (int)S.size()) {
        // S is valid, thus we can use the first char to parse
        if (std::isdigit(S[i])) {
            // case push
            // input says X is always 0 and 2^20 - 1,
            // so no need to parse negative sign.
            int cur = i;
            while (i < (int)S.size() && std::isdigit(S[i])) {
                i++;
            }
            int val = stoi(S.substr(cur, i - cur));
            m.push_back(val);
            i++; continue;
        } else if (S[i] == 'P') {
            // case pop
            if (m.empty()) return -1;
            m.pop_back();
            i += 4; continue;
        } else if (S[i] == 'D') {
            // case dup
            if (m.empty()) return -1;
            m.push_back(m.back());
            i += 4; continue;
        } else if (S[i] == '+') {
            if (m.size() < 2) return -1;
            int l = m.back(); m.pop_back();
            int r = m.back(); m.pop_back();
            if (l + r > maxV) {
                return -1;
            }
            m.push_back(l + r);
            i += 2; continue;
        } else if (S[i] == '-') {
            if (m.size() < 2) return -1;
            int l = m.back(); m.pop_back();
            int r = m.back(); m.pop_back();
            if (l < r) {
                return -1;
            }
            m.push_back(l - r);
            i += 2; continue;
        } else {
            // impossible
            return -1;
        }
    }

    if (m.empty()) {
        return -1;
    }
    return m.back();
}

int main() {
   vector<pair<string, int>> Ss {
      // long seq
      {"1 2 DUP + + DUP - 1 +", 1},
      {"13 DUP 4 POP 5 DUP + DUP + -", 7},
      {"5 6 + -", -1},
      {"3 DUP 5 - -", -1},
      {"3 5 -", 2},
      {"5 3 -", -1},
      {"1048575 0 +", 1048575},
      {"1048575 1048573 -", -1},
      // cannot pop
      {"POP", -1},
      {"1 2 POP POP POP", -1},
      {"1 2 - POP POP", -1},
      // empty stack
      {"1 2 - POP", -1},
      // cannot dup
      {"1 2 POP POP DUP", -1},
      {"DUP", -1},
      {"1 2 - POP DUP", -1},
      // overflow
      {"1048575 1 +", -1},
      {"1048575 1048575 +", -1},
      // not overflow
      {"1048575 1048575 -", 0},
      // underflow
      {"2 1 -", -1},
      {"2 1 3 POP -", -1},
      {"2 4 5 - -", -1},
      // not underflow
      {"2 3 1 POP -", 1},
      {"2 4 6 - -", 0},
      // empty state:
      {"2 POP", -1},
      {"1 1 + POP", -1},
      // leading 0?
      // note the problem says X is always a number in [0, 2^20)
      {"001 100 +", 101},
      {"001 100 -", 99},
      // not enough operand:
      {"-", -1},
      {"+", -1},
      {"1 -", -1},
      {"1 +", -1},
      {"10 -", -1},
      {"10 +", -1},
      {"13 10 POP +", -1},
      {"13 DUP POP +", -1},
      {"13 10 POP -", -1},
      {"13 DUP POP -", -1},
   };

   for (auto s : Ss) {
      int out = solution(s.first);
      if (out != s.second) {
         cout << "in:" << s.first << endl;
         cout << "out:" << out << endl;
      }
      assert(s.second == out);
   }
   cout << "...Passed" << endl;
   return 0;
}

