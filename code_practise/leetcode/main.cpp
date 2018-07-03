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

int main() {
   ss68::test();
   cout << "Passed..." << endl;
}
