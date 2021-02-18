class Solution {
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    bool search(vector<vector<char>> &g, int x, int y, const string &target, int idx) {
        if (idx == target.size()) {
            return true;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= g.size() || ny < 0 || ny >= g[0].size() || target[idx] != g[nx][ny]) {
                continue;
            }

            g[nx][ny] = '@';
            if (search(g, nx, ny, target, idx+1)) {
                return true;
            }
            g[nx][ny] = target[idx];
        }

        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.size() == 0) return word.size() == 0;
        if (word.size() == 0) return true;
        for (int x = 0; x < board.size(); ++x) {
            for (int y = 0; y < board[0].size(); ++y) {
                if (word[0] != board[x][y]) continue;
                board[x][y] = '@';
                if (search(board, x, y, word, 1)) {
                    return true;
                }
                board[x][y] = word[0];
            }
        }

        return false;
    }
};