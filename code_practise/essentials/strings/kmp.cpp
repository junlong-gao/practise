#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <cassert>
#include <deque>

using namespace std;

class KMP {
  /*
   * KMP
   *
   * KMP is a special case of AC Automa, where the entire trie has one single
   * branch. Also, there is no output link as we only have one pattern.
   *
   * Suffix link can be compactly represented as an array: sl[i] is the longest
   * prefix being p[0...i]'s proper suffix. p[0] = -1;
   *
   * To use the suffix array, use the same invariant in AC automa: idx is the
   * trie node matching a longest prefix being suffix of m[0...i-1] for text
   * m, at index i. Now, use suffix link to update idx as long as p[idx + 1] !=
   * m[i];
   */

public:
   vector<int> sl;
   string pattern_;

   KMP(
     const string &pattern
   ) {
      assert(pattern.length());
      sl.resize(pattern.size());
      pattern_ = pattern;
      sl[0] = -1;
      for (int i = 1; i < pattern.length(); ++i) {
         int idx = sl[i - 1];
         while (idx != -1 && pattern[i] != pattern[idx + 1]) {
            idx = sl[idx];
         }

         if (pattern[idx + 1] == pattern[i]) {
            sl[i] = idx + 1;
         } else {
            sl[i] = -1;
         }
      }
   }

   void match(const string &m, vector<int> &output) {
      int idx = -1;
      for (int i = 0; i < m.length(); ++i) {
         while (idx != -1 && m[i] != pattern_[idx + 1]) {
            idx = sl[idx];
         }
         if (pattern_[idx + 1] == m[i]) {
            idx = idx + 1;
            if (idx == pattern_.size() - 1) {
               output.push_back(i);
            }
         }
      }
   }
};

int main() {
  KMP kmp { "abba" };

  auto findAndPrint = [&kmp] (const string & m) {
     vector<int> ret;
     kmp.match(m, ret);
     cout << "matched for " << m << ":" << endl;
     for (auto &w : ret) {
       cout << "  " << w << endl;
     }
     cout << "--" << endl;
  };

  findAndPrint("abba");
  findAndPrint("ababba");
  findAndPrint("aabbabba");
  findAndPrint("ababa");

  cout << "Done" << endl;
  return 0;
}
