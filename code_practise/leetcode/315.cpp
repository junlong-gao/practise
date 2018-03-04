/*
 *
> leetcode submit 315.cpp
  ✔ Accepted
  ✔ 16/16 cases passed (37 ms)
  ✔ Your runtime beats 43.62 % of cpp submissions
  */
class Solution {
   using pr = pair<int, int>;
   vector<pr> arr;
   vector<int> table;
   vector<pr> merge(int s, int e) {
      if (e - s == 0) return {};
      if (e - s == 1) return {arr[s]};
      int mid = s + (e - s) / 2;
      vector<pr> l, r, ret;
      l = merge(s, mid);
      r = merge(mid, e);
      int i = 0, j = 0;
      while (i < l.size() && j < r.size()) {
         if (l[i].first <= r[j].first) {
            table[l[i].second] += j;
            ret.push_back(l[i++]);
         } else {
            ret.push_back(r[j++]);
         }
      }

      while (i < l.size()) {
         table[l[i].second] += j;
         ret.push_back(l[i++]);
      }

      while (j < r.size()) {
         ret.push_back(r[j++]);
      }

      return ret;
   }
public:
    vector<int> countSmaller(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
           arr.push_back({nums[i], i});
        }

        table.resize(nums.size(), 0);
        merge(0, nums.size());
        return table;
    }
};


/*
TESTS
[1]
[2, 1]
[2, 2]
[3, 2, 1]
[3, 2, 2]
[5, 2, 6, 1]
*/
