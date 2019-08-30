class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
      if (A.empty()) return 0;
      // dp1[i]: opt end in i with swap, dp2[i]: opt end in i without swap
      vector<int> dp1(A.size(), A.size()), dp2(A.size(), A.size());
      dp1[0] = 1; dp2[0] = 0;
      for (int i = 1; i < A.size(); ++i) {
          if (A[i] > B[i - 1] && B[i] > A[i - 1]) {
              dp1[i] = dp2[i - 1] + 1;
              dp2[i] = dp1[i - 1];
          }
          
          if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
              dp1[i] = min(dp1[i], dp1[i - 1] + 1);
              dp2[i] = min(dp2[i], dp2[i - 1]);
          }
      }
       return min(dp1.back(), dp2.back());
    }
};
