/*
what is the size (bits) of the input? 32
preconstruct a table.
let hashTable = all possible power of 2
return n is in hashTable

2’s complement representation?
*/

class Solution {
 public:
  bool isPowerOfTwo(int n) {
    static const unordered_set<int> table = [&]() {
      unordered_set<int> ret;
      for (int i = 0; i < 32; ++i) {
        ret.insert(1 << i);
      }
      return ret;
    }();
    return table.count(n) == 1;
  }
};

/*
2’s complement representation, -2147483648 has the same form of 2147483648 !!
while the latter is not representable (remember, if the MSB is 1, it is
negative).
*/
