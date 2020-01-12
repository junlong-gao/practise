#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
   int N; cin >> N;

   vector<int> cow;
   while (N-->0) {
      char c; cin >> c;
      if (c == 'B') {
         cow.push_back(1);
      } else {
         cow.push_back(0);
      }
   }

   N = cow.size();

   int best = INT_MAX; int bestK = -1;
   for (int K = 1; K <= N; ++K) {
      int win = 0;
      int res = 0;
      vector<int> rotate(N, 0);
      for (int i = 0; i + K <= N; ++i) {
         if ((cow[i] + win) % 2) {
            rotate[i] = 1;
            res++;
         }
         win += rotate[i];
         if (i - K + 1 >= 0) {
            win -= rotate[i - K + 1];
         }
      }


      for (int i = N - K + 1; i < N; ++i) {
         if ((cow[i] + win) % 2) {
            res = INT_MAX;
            break;
         }
         if (i - K + 1 >= 0) {
            win -= rotate[i - K + 1];
         }
      }

      if (res < best) {
         //cout << "XXX " << res << " " << K << endl;
         best = res; bestK = K;
      }
   }
   cout << bestK << " " << best << endl;
   return 0;
}
