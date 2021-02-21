class Solution {
   int count;
   int s, e;
   unordered_map<int, int> shuffle;
public:
    Solution(int N, vector<int> blacklist) {
       s = 0; e = N;
       for (auto v : blacklist) {
          if (v < e && v >= s) {
             shuffle[v] = -1;
          }
       }


       count = e - s - shuffle.size();
       int cur = s + count;

       for (auto pr : shuffle) {
          int v = pr.first;
          if (v < s + count && v >= s) {
             while (shuffle.count(cur)) {
                cur++;
             }
             shuffle[v] = cur++;
          }
       }

       // seed
       srand(time(nullptr));
    }

    int pick() {
       int pick = s + rand() % count;
       if (shuffle.count(pick)) return shuffle[pick];
       return pick;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(N, blacklist);
 * int param_1 = obj.pick();
 */
