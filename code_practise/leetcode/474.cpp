/*
dp[i][n][m] = # opt of subproblem arr[0..i-1] taken arr[i-1] with n 1's and m 0's.
dp[i][n][m] = if arr[i-1] is not viable return 0
	        else 1 + max_{0 <= j < i} dp[j][n - count_1(arr[i-1])][m - count_0(arr[i-1])] + 1
10, 0001, 111001, 1, 0
m = 5, n = 3
count_0: 1, 3, 2, 0, 1
count_1: 1, 1, 4, 1, 0
solve(0, 5, 3) -> 1;
solve(1, 5, 3) [2, 2] -> solve(0, 2, 2) -> 1 -> 2
solve(2, 5, 3) -> 0
solve(3, 5, 3) [5, 2] -> solve(2, 5, 2) -> 0 -> 1
		        |   solve (1, 5, 2) [2, 1] -> solve(0, 2, 1) -> 1 -> 2 -> 3
		        |   solve(0, 5, 2) -> 1 -> 2
solve(4, 5, 3) [4, 3] -> solve(3, 4, 3) [4, 2] -> solve(2, 4, 2)
						| solve(1, 4, 2) [1, 1] -> solve(0, 1, 1) -> 1 -> 2 -> 3 -> 4
        |   solve(2, 4, 3) -> 0 -> 1
		        |   solve(1, 4, 3) [1, 2] -> solve(0, 1, 2) -> 1 -> 2 -> 3

*/
class Solution {
	vector<int> count_1, count_0;
	int countZero(const string &s) {
		int ret = 0;
		for (int i = 0; i < s.size(); +i) {
			if (s == '0') ret++;
		}
		return ret;
	}
	unordered_map<unordered_map<unordered_map<int, int>, int>, int> dp;
	bool computed(int idx, int m, int n) {
		if (dp.count(idx) == 0) return false;
		if (dp[idx].count(m) == 0) return false;
		if (dp[idx][m].count(n) == 0) return false;
		return true;
	}
	int solve(int idx, int m, int n) {
		if (computed(idx, m, n)) return dp[idx][m][n];
		if (count_0[idx] > m || count_1[idx] > n) return 0;
		m -= count_0[idx];
		n  -= count_1[idx];
		dp[idx][m][n] = 1;
		for (int j = 0; j < i; ++j) {
			dp[idx][m][n] = max(dp[idx][m][n], solve(j, m, n) + 1);
		}
		return dp[idx][m][n];
	}
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
       	for (const auto & s: strs) {
		count_0.push_back(countZero(s));
		count_1.push_back(s.length() - count_0.back());
	}
	int best = 0;
	for (int i = 0; i < strs.length(); ++i) {
		best = max(best, solve(idx, m, n));
	}
	return best;
    }
};

