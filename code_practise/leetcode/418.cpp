#include <bits/stdc++.h>
using namespace std;
#define ASSERT assert

/*
 * Digestion:
 * For each line, it must start with a certain word idx.
 * Even though the number of rows is huge (20000), the possible starting
 * word is limited (<=100). If we know the starting word, the entire line
 * layout is fixed.
 * So we can simply cache the line layout for each word as the starting word.
 *
 * To cache layout, we just need to know how many words fit in the line.
 */

class Solution {
public:
    int wordsTyping(const vector<string>& sentence, int rows, int cols) {
       int total = 0; int numWords = sentence.size();
       unordered_map<int, int> cache;
       for (int i = 0; i < rows; ++i) {
          int idx = total % numWords;
          if (0 == cache.count(idx)) {
             int &count = cache[idx];
             for (int cur = 0, j = idx;
                  cur + sentence[j % numWords].size() <= cols;
                  cur += sentence[j % numWords].size() + 1, ++j) { // XXX order of ++j matters
                count++;
             }
             total += count;
          } else {
             total += cache[idx];
          }
       }
       return total / numWords;
    }
};

int main() {
   Solution s;

   ASSERT(
   1
   ==
   s.wordsTyping
   (

   {"I", "had", "apple", "pie"},
   4,
   5

   ));

   ASSERT(
   3
   ==
   s.wordsTyping
   (

   {"I", "had", "apple", "pie"},
   9,
   5

   ));

   ASSERT(
   2
   ==
   s.wordsTyping
   (

   {"a", "bcd", "e"},
   3,
   6

   ));

   ASSERT(
   1
   ==
   s.wordsTyping
   (

   {"hello", "world"},
   2,
   8

   ));

   return 0;
}

/*
TESTS

*/
