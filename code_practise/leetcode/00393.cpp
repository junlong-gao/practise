
/*
Once you read the first char's 5 bits, you know the layout:
(0)0xxxx -> 1 layout -> 0
(6)110xx -> 2 -> 1
(14)1110x -> 3 -> 2
(30)11110 -> 4 -> 3

(2)10

*/
class Solution {
 public:
  bool validUtf8(vector<int>& data) {
    int idx = 0;
    int mask = 0x000000FF;
    while (idx < data.size()) {
      int lead = (data[idx] & mask);
      int toCheck = -1;
      if ((lead >> 3) == 30) {
        toCheck = 3;
      } else if ((lead >> 4) == 14) {
        toCheck = 2;
      } else if ((lead >> 5) == 6) {
        toCheck = 1;
      } else if ((lead >> 7) == 0) {
        toCheck = 0;
      }
      if (toCheck == -1) return false;
      idx++;
      if (idx + toCheck > data.size()) return false;
      for (int i = idx; i < idx + toCheck; ++i) {
        int d = (data[i] & mask);
        if (2 != (d >> 6)) return false;
      }
      idx += toCheck;
    }

    return true;
  }
};

/*
11000101 10000010 00000001

Bit manipulation. Mask is wrong

*/


Format!Style:
C++ online code formatter © 2014 by KrzaQ

Powered by vibe.d, the D language and clang-format
