// fogive me... this is just a demo
#include <bits/stdc++.h>
using namespace std;

namespace bit_normal {

struct bit {
  vector<int> b;
  int n;
  bit(const vector<int> &arr) {
    n = arr.size();
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

   int n = in.size();
   bit bitTest{in};
   vector<int> out(n, 0);
   auto sum_out = [&](int n) {
      int ret = 0;
      for (int i = 0; i <= n; i++) {
         ret += in[i];
      }
      return ret;
   };
   auto assert_out = [&]() {
      for (int i = 0; i < n; i++) {
         assert(sum_out(i) == bitTest.sum(i));
      }
   };

   assert_out();

   bitTest.update(1, 5 - in[1]);
   in[1] = 5;
   assert_out();

   cout << "Passed..." << endl;
}

struct bit_2d {
  vector<vector<int>> b;
  int n, m;
  bit_2d(const vector<vector<int>> &arr) {
    n = arr.size();
    if (n == 1) return;
    m = arr[0].size();
    b.resize(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i < n; ++i) {
       for (int j = 0; j < m; ++j) {
          update(i, j, arr[i][j]);
       }
    }
  }

  void update(const int row, const int col, const int u) {
    unsigned int i = row + 1;
    while (i <= n) {
       unsigned int j = col + 1;
       while (j <= m) {
         b[i][j] += u;
         j += j & (-j);
       }

       i += i & (-i);
    }
  }

  int sum(const int row, const int col) {
     int ret = 0;
     unsigned int i = row + 1;
     while (i) {
        unsigned int j = col + 1;
        while (j) {
           ret += b[i][j];
           j -= j & (-j);
        }

        i -= i & (-i);
     }

     return ret;
  }

};

void test_2d() {
   vector<vector<int>> in
     {
        {1, 2, 3, 4, 5},
        {2, 4, 6, 8, 10},
        {3, 6, 9, 12, 15},
     };

   int n = in.size();
   int m = in[0].size();
   bit_2d bitTest{in};
   vector<vector<int>> out(n, vector<int>(m, 0));
   auto sum_out = [&](int n, int m) {
      int ret = 0;
      for (int i = 0; i <= n; i++) {
         for (int j = 0; j <= m; ++j) {
            ret += in[i][j];
         }
      }
      return ret;
   };
   auto assert_out = [&]() {
      for (int i = 0; i < n; i++) {
         for (int j = 0; j < m; ++j) {
            assert(sum_out(i, j) == bitTest.sum(i,j));
         }
      }
   };

   assert_out();

   bitTest.update(1, 2, 5 - in[1][2]);
   in[1][2] = 5;
   assert_out();

   cout << "Passed..." << endl;
}

}
