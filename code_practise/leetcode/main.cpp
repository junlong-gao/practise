#include "helper.hpp"

namespace ss68 {
#include "68.text-justification.cpp"
void test() {
   cout << "debug 68" << endl;
   Solution s;
   {
      vector<string> words = {
         "aa", "aa", "aa", "a",
         "aa", "aa", "a"
      };
      int L = 10;
      cout << s.fullJustify(words, L) << endl;
   }
   {
      vector<string> words = {
         "aa", "aa", "aa", "aa",
         "aa", "aa", "aa", "aa",
         "aa", "aa", "aa", "aa",
         "aa", "aa", "a"
      };
      int L = 10;
      cout << s.fullJustify(words, L) << endl;
   }
   {
      vector<string> words = {
         "aa", "aa", "aa", "a",
         "aa", "aa", "a"
      };
      int L = 2;
      cout << s.fullJustify(words, L) << endl;
   }
   {
      vector<string> words = {
         "aa", "aa", "aa", "a",
         "aa", "aa", "aa", "a"
      };
      int L = 10;
      cout << s.fullJustify(words, L) << endl;
   }

   {
      vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
      int L = 16;
      cout << s.fullJustify(words, L) << endl;
   }
}
}

namespace ss864 {
#include "864.cpp"
   void test() {
      int N = 20; vector<int> l {0, 1, 2,4,5,8,9,10,15,16,19, 19, 20, 21, 22, 22}; 
      unordered_map<int, int> hist;
      Solution s(N, l);
      
      for (int i = 0; i < 1000; ++i) {
         hist[s.pick()]++;
      }
      cout << l << endl;
      cout << hist << endl;
      return;
   }
}

int main() {
   ss68::test();
   ss864::test();
   cout << "Passed..." << endl;
}
