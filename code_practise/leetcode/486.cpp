/*
[i...j] -> pick i -> f([i...j]) = S[i...j] - f([i+1...j])
	pick j -> f([i...j]) = S[i...j] - f([i, j - 1])
win if f([i..j]) >= half
*/
class Solution {
    vector<long long> S;
	vector<vector<long long>> dp;
	int n;
	int opt(int i, int j) {
		if (i > j) return 0;
		if (dp[i][j] != -1) return dp[i][j];
		long long TS = S[j + 1] - S[i];
		long long l = opt(i+1, j);
		long long r = opt(i, j - 1);
		dp[i][j] = max(TS - l, TS - r);
		return dp[i][j];
	}
public:
    bool PredictTheWinner(vector<int>& nums) {
	n = nums.size();
	S.push_back(0);
        	for (int i = 0; i < nums.size(); ++i) {
		S.push_back(S.back() + nums[i]);
	}

	dp.resize(n, vector<long long>(n, -1));
	long long ret = opt(0, n - 1);
	return ret >= (S[n] - S[0] - ret);
    }
};

