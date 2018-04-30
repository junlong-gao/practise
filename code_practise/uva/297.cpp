#include <bits/stdc++.h>
using namespace std;

class solver {
   static constexpr int size = 32;
   const char *cur;
   int buf[size + 1][size + 1];
   int dfs(int x, int y, int l) {
      int total = 0;
      const char c = *(cur++);
      if (c == 'p') {
         total += dfs(x, y + l / 2, l / 2);
         total += dfs(x, y, l / 2);
         total += dfs(x + l / 2, y, l / 2);
         total += dfs(x + l / 2, y + l / 2, l / 2);
      }
      if (c == 'f') {
         for (int xx = x; xx < x + l; ++xx) {
            for (int yy = y; yy < y + l; ++yy) {
               if (buf[xx][yy] == 0) {
                  buf[xx][yy] = 1;
                  total++;
               }
            }
         }
      }
      return total;
   }

public:
   int solve(const char *in1, const char *in2) {
      memset(buf, 0, sizeof(buf));
      cur = in1;
      int first = dfs(0, 0, size);
      cur = in2;
      int second = dfs(0, 0, size);
      return first + second;
   }
} s;

int main() {
   int count;
   cin >> count;
   while (count --> 0) {
      string preorder1, preorder2;
      cin >> preorder1 >> preorder2;
      int out = s.solve(preorder1.c_str(), preorder2.c_str());
      printf("There are %d black pixels.\n", out);
   }
}