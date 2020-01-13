#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
   int T = 0;
   while (true) {
      T++;
      int n; cin >> n;
      if (n == 0) {
         break;
      }
      vector<double> x1, x2, y1, y2, xs, ys;
      for (int i = 0; i < n; ++i) {
         x1.push_back(0);
         x2.push_back(0);
         y1.push_back(0);
         y2.push_back(0);
         cin >> x1.back() >> y1.back() >> x2.back() >> y2.back();
         xs.push_back(x1.back());
         xs.push_back(x2.back());
         ys.push_back(y1.back());
         ys.push_back(y2.back());
      }
      sort(xs.begin(), xs.end());
      sort(ys.begin(), ys.end());
      int xs_n = unique(xs.begin(), xs.end()) - xs.begin();
      int ys_n = unique(ys.begin(), ys.end()) - ys.begin();
      double area = 0;
      for (int i = 0; i + 1< xs_n; ++i) {
         for (int j = 0; j + 1 < ys_n; ++j) {
            for (int k = 0; k < n; ++k) {
               if (xs[i] >= x1[k] &&
                   xs[i + 1] <= x2[k] &&
                   ys[j] >= y1[k] &&
                   ys[j + 1] <= y2[k]) {
                  //cout << xs[i + 1] << " " << xs[i] << " " << ys[i + 1] << " " << ys[i] << endl;
                  area += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
                  break;
               }
            }
         }
      }
      printf("Test case #%d\n", T);
      printf("Total explored area: %.2f\n", area);
      printf("\n");
   }

   return 0;
}
