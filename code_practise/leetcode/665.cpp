class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
      if (nums.size() < 3) return true;
      int count = 1;
      for (int i = 1; i + 1 < nums.size(); ++i) {
       int &l = nums[i-1]; int &m = nums[i]; int &r = nums[i+1];
       if (l <= m && m <= r) continue;
       if (count == 0) return false;
       if (l > r) {
         if (m > r) {
           if (m < l) return false;
           r = m;
         } else {
           l = m;
         }
       } else {
         m = r;
       }
       count--;
      }
      return true;
    }
};