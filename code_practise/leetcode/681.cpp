class Solution {
   array<int, 2> current;
   array<int, 2> next;

   bool valid() {
      if (next[0] >= 24 || next[0] < 0) return false;
      if (next[1] < 0 || next[1] > 59) return false;
      return true;
   }

   int delta() {
      const int M = 60 * 24;
      return ((next[0] * 60 + next[1]) - (current[0] * 60 + current[1]) + M) % M;
   }

public:
    string nextClosestTime(string time) {
       current[0] = stoi(time.substr(0, 2));
       current[1] = stoi(time.substr(3, 2));
       unordered_set<int> digits;
       for (int i = 0; i < time.size(); ++i) {
          char c = time[i];
          if (i == 2) continue;
          digits.insert(c - '0');
       }

       int best = INT_MAX;
       array<int, 2> ret;
       for (auto d1 : digits) {
          for (auto d2: digits) {
             next[0] = d1 * 10 + d2;
             for (auto d3 : digits) {
                for (auto d4 : digits) {
                   next[1] = d3 * 10 + d4;
                   if (!valid()) continue;
                   int rst = delta();
                   if (rst < best && rst != 0) {
                      ret = next;
                      best = rst;
                   }
                }
             }
          }
       }

       if (best == INT_MAX) return time;

       string hour, minutes;
       for (int i = 0; i < 2; ++i) {
          hour.push_back(ret[0] % 10 + '0');
          ret[0] /= 10;
       }
       reverse(hour.begin(), hour.end());
       for (int i = 0; i < 2; ++i) {
          minutes.push_back(ret[1] % 10 + '0');
          ret[1] /= 10;
       }
       reverse(minutes.begin(), minutes.end());
       return hour + ":" + minutes;
    }
};

/*
TESTS

*/

/*
Bite: what if there is no next time?
*/