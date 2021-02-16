// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        while (true) {
            int a = rand7() - 1; int b = rand7() - 1;
            int dec = a * 7 + b;
            if (dec > 39) continue;
            return dec / 4 + 1;
        }
    }
};