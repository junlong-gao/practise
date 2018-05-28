class Solution {
    unordered_map<int, bool> dp;
    int l;
	bool f(int d, int s) {
        if (dp.count(s) != 0) return dp[s];
		if (d <= 0) return false;
		for (int i = 0; i < l; ++i) {
			if (s & (1 << i)) continue;
			s |= (1 << i);
            bool ret = f(d - i - 1, s);
            s &= ~(1 << i);

			if (!ret) {
                dp[s] = true;
				return true;
			}
		}
        dp[s] = false;
		return false;
	}
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
    if (desiredTotal == 0) return true;
	if (maxChoosableInteger * (1 + maxChoosableInteger) < 2 * desiredTotal) return false;
    l = maxChoosableInteger;
	return f(desiredTotal, 0);
    }
};

