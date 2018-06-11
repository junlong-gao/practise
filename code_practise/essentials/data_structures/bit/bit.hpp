// fogive me... this is just a demo
#include <bits/stdc++.h>
using namespace std;

namespace bit_normal {

struct bit {
  vector<int> b;
  int n;
  bit(const vector<int> &arr) {
    n = arr.size() + 1;
    b.resize(n+1);
    for (int i = 0; i < n; ++i) {
       update(i, arr[i]);
    }
  }

  void update(const int idx, const int x) {
    unsigned int i = idx + 1;
    while (i <= n) {
       b[i] += x;
       i += i & (-i);
    }
  }

  int sum(const int idx) {
     int ret = 0;
    unsigned int i = idx + 1;
     while (i) {
        ret += b[i];
        i -= i & (-i);
     }

     return ret;
  }

};

void test() {
   vector<int> in {1, 2, 3, 4, 5};
   bit bitTest{in};
   int t = 0;
   for (int i = 0; i < 5; ++i) {
      t += in[i];
      assert(bitTest.sum(i) == t);
   }

   int idx = 2, val = -2;
   bitTest.update(idx, val - in[idx]);
   in[idx] = val;
   t = 0;
   for (int i = 0; i < 5; ++i) {
      t += in[i];
      assert(bitTest.sum(i) == t);
   }

   cout << "Passed..." << endl;
}

}