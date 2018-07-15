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
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int n = sentence.size();
        vector<int> dp(n, -1);
        int usedWords = 0;
        for (int i = 0; i < rows; ++i) {
            if (dp[usedWords % n] >= 0) {
                usedWords += dp[usedWords % n];
                continue;
            }

            int old = usedWords;
            int left = cols;
            while (left >= sentence[usedWords % n].length()) {
                if (left >= sentence[usedWords % n].length() + 1) {
                    left -= 1;
                }
                left -= sentence[usedWords % n].length();
                usedWords++;
            }
            dp[old % n] = usedWords - old;
        }

        return usedWords / n;
    }
};
