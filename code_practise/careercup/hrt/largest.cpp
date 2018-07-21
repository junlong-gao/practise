#include <iostream>
#include <vector>

using namespace std;
/*
A = ...x...y...
B = ...y...x...

xy < yx => A < B

*/

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [&](int l, int r){
            return to_string(r) + to_string(l) < to_string(l) + to_string(r);
        });
        string init {""};
        for (auto e : nums) {
            init += to_string(e);
        }
        // handle leading 0s
        int buf = 0;
        for (int i = 0; i < init.length(); ++i) {
            if (init[i] == '0') buf++;
            else break;
        }
        if (buf == init.length()) return "0";
        return init.substr(buf, init.length() - buf);
    }
};

int main() {
   {
      Solution s;
      vector<int> vals {0, 1, 2, 3};
      cout << s.largestNumber(vals) << endl;
   }
   {
      Solution s;
      vector<int> vals {10, 20, 30, 0};
      cout << s.largestNumber(vals) << endl;
   }
   return 0;
}
