class Solution {
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    bool search(int idx, const string &s,
                int x, int y,
                vector<vector<char>> &g,
                vector<vector<bool>> &vis,
                vector<string> *output) {
        if (idx == s.size() - 1) {
            output->push_back(s);
            return true;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= g.size() || ny < 0 || ny >= g[0].size() || vis[nx][ny] || g[nx][ny] != s[idx + 1]) {
                continue;
            }

            vis[nx][ny] = true;
            if (search(idx + 1, s, nx, ny, g, vis, output))  {
                return true;
            }
            vis[nx][ny] = false;
        }

        return false;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.empty()) {
            return {};
        }
        if (words.empty()) {
            return {};
        }
        unordered_set<string> found;
        for (auto &w : words) {
            if (found.count(w) == 0 && w.size()) {
                found.insert(w);
            }
        }

        vector<string> ret;
        for (auto & w : found) {
            bool got = false;
            for (int i = 0; i < board.size(); ++i) {
                if (got) break;
                for (int j = 0; j < board[i].size(); ++j) {
                    if (board[i][j] != w[0]) {
                        continue;
                    }

                    vector<vector<bool>> vis(board.size(), vector<bool>(board[0].size(), false));
                    vis[i][j] = true;
                    got = search(0, w, i, j, board, vis, &ret);
                    if (got) { break; }
                }
            }
        }
        return ret;
    }
};