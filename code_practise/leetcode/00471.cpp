class Solution {
    string s;
    int n;
    vector<vector<int>> dp;
    vector<vector<int>> ans;
    vector<vector<int>> p;

    int solver(int i, int j) {
        assert(i <= j);
        //cout << i <<  " " << j << " "  << dp[i][j] << endl;
        if (i == j) return  1;
        
        if (ans[i][j] != 0) return ans[i][j];
        
        int & ret = ans[i][j];
        // case 1: entire i to j is a repeat pattern
        int length = (j - i + 1) / dp[i][j];
        if (dp[i][j] == 1) {
            // -1
            ret = length;
            p[i][j] = -1;
        } else {
            // -2
            ret = to_string(dp[i][j]).length() + 2 + solver(i, i + length - 1);
            p[i][j] = -2;
        }
        
        // case 2:
        for (int k = i; k < j; ++k) {
            int left = solver(i, k);
            int right = solver(k + 1, j);
            if (ret >= left + right) {
                p[i][j] = k;
                ret = left + right;
            }
        }
        return ret;
    }
    
    string construct(int i, int j) {
        if (i == j) return s.substr(i, 1);
        int op = p[i][j];
        //cout << op << endl;
        if (op >= 0) {
            string left = construct(i, op);
            string right = construct(op + 1, j);
            return left + right;
        }
        int length = (j - i + 1) / dp[i][j];
        if (op == -1) {
            return s.substr(i, length);
        }
        if (op == -2) {
            return to_string(dp[i][j]) + "[" + construct(i, i + length - 1) + "]";
        }
        assert(0);
    }
    
public:
    string encode(string ss) {
        swap(s, ss);
        n = s.length();
        dp = vector<vector<int>>(n, vector<int>(n, 0));
        ans = dp; p = dp;

        for (int l = 1; l <= n; ++l) {
            for (int i = 0; i + l - 1 < n; ++i) {
                int j = i + l - 1;
                dp[i][j] = 1;
                if (l == 1) {
                    continue;
                }
                for (int k = i; k < j; ++k) {
                    const int left = dp[i][k];
                    const int right = dp[k + 1][j];
                    assert((k - i + 1) % left == 0);
                    assert((j - k) % right == 0);
                    const int ll = (k - i + 1) / left;
                    const int lr = (j - k) / right;
                    
                    if (ll != lr || s.substr(i, ll) != s.substr(k + 1, lr)) {
                        continue;
                    }
                    dp[i][j] = std::max(dp[i][j], left + right);
                }
            }
        }
        
        int rst = solver(0, n - 1);
        //cout << rst << endl;
        return construct(0, n - 1);
    }
};
