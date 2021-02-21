class Solution {
    vector<vector<int>> skips{10, vector<int>(10, 0)}; // i -> j need pass skips[i][j];
    int search(int last, vector<bool> &used, int len, int target) {
        if (len == target) {
            return 1;
        }

        int ret = 0;
        for (int i = 1; i <= 9; ++i) {
            if (used[i]) continue;
            if (len != 0 && skips[last][i] != 0 && !used[skips[last][i]]) continue;
            used[i] = true;
            ret += search(i, used, len + 1, target);
            used[i] = false;
        }

        return ret;
    }
public:
    int numberOfPatterns(int m, int n) {
        skips[1][3] = skips[3][1] = 2;
        skips[1][7] = skips[7][1] = 4;
        skips[1][9] = skips[2][8] = skips[3][7] = skips[4][6] = 5;
        skips[9][1] = skips[8][2] = skips[7][3] = skips[6][4] = 5;
        skips[3][9] = skips[9][3] = 6;
        skips[7][9] = skips[9][7] = 8;
        vector<bool> used(10, false);
        int ret = 0;
        for (int l = m; l <= n; ++l) {
            ret += search(0, used, 0, l);
        }

        return ret;
    }
};