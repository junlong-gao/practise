class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        vector<vector<int>> &rec = rectangles;
        int n = rec.size();
        vector<int> fx(2*n + 1, 0), fy(2*n + 1, 0);
        for (int i = 0; i < n; ++i) {
            fx[2*i]     = rec[i][0];
            fx[2*i+1]   = rec[i][2];
            fy[2*i]     = rec[i][1];
            fy[2*i + 1] = rec[i][3];
        }
        sort(fx.begin(), fx.end());
        fx.erase(unique(fx.begin(), fx.end()), fx.end());
        
        sort(fy.begin(), fy.end());
        fy.erase(unique(fy.begin(), fy.end()), fy.end());

        unsigned long long ans = 0, M = 1e9 + 7;
        for (int i = 1; i < fx.size(); ++i) {
            for (int j = 1; j < fy.size(); ++j) {
                for (auto & r : rec) {
                    if (fx[i - 1] >= r[0] &&
                        fx[i]     <= r[2] &&
                        fy[j - 1] >= r[1] &&
                        fy[j]     <= r[3]) {
                        unsigned long long dx = fx[i] - fx[i - 1];
                        unsigned long long dy = fy[j] - fy[j - 1];
                        ans = (ans + (dx * dy) % M) % M;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};

/*
pixelate the graph. For each unit patch in the pixelate graph, count
its contribution if and only if it is in some original rec.

Use unique to reduce cases where dx = 0 or dy = 0 (but not impact correctness).
*/

/*
Alternative: Line sweep
*/
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        unsigned long long M = 1e9 + 7;
        unordered_map<int, vector<int>> entering, leaving;
        vector<int> xs;
        for (int i = 0; i < rectangles.size(); ++i) {
            entering[rectangles[i][0]].push_back(i);
            leaving[rectangles[i][2]].push_back(i);
            xs.push_back(rectangles[i][0]);
            xs.push_back(rectangles[i][2]);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        unordered_set<int> cur;
        
        unsigned long long ret = 0;
        for (int i = 0; i + 1 < xs.size(); ++i) {
            for (int idx : leaving[xs[i]]) {
                cur.erase(idx);
            }
            for (int idx : entering[xs[i]]) {
                cur.insert(idx);
            }
            
            vector<int> exts(cur.begin(), cur.end());
            sort(exts.begin(), exts.end(), [&rectangles](int l, int r) {
                if (rectangles[l][1] != rectangles[r][1]) {
                    return rectangles[l][1] < rectangles[r][1];
                }
                if (rectangles[l][3] != rectangles[r][3]) {
                    return rectangles[l][3] < rectangles[r][3];
                }
                return l < r;
            });
            
            vector<pair<int, int>> sortedExt;
            for (int j = 0; j < exts.size(); ++j) {
                if (sortedExt.empty() || 
                    sortedExt.back().second < rectangles[exts[j]][1]) {
                    sortedExt.push_back(
                        make_pair(rectangles[exts[j]][1], rectangles[exts[j]][3]));
                } else {
                    sortedExt.back().second = 
                        max(sortedExt.back().second, rectangles[exts[j]][3]);
                }
            }
            
            unsigned long long w = xs[i + 1] - xs[i];
            for (int j = 0; j < sortedExt.size(); ++j) {
                ret = (ret + (w * (sortedExt[j].second - sortedExt[j].first)) % M) % M;

            }
        }
        
        return ret;
    }
};
