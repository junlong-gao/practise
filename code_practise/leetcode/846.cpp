class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int W) {
       map<int, int> refcount;
       for (auto e : hand) {
          refcount[e]++;
       }
       while (refcount.size()) {
          int w = 0;
          int prev = 0;
          auto it = refcount.begin();
          while (w < W) {
             if (it == refcount.end()) {
                return false;
             }
             if (w > 0 && it->first != prev+1) {
                return false;
             }
             it->second--;
             prev=it->first;
             w++;
             if (it->second == 0) {
                it = refcount.erase(it);
             } else {
                ++it;
             }
          }
       }
       return true;
    }
};
