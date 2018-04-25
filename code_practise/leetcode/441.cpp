class Solution {
public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        auto check = [&](int bits, const string & v) {
            for (int i = 0; i < v.size(); ++i) {
                if (bits & (1 << i) && v[i] != target[i]) {
                    return true;
                }
            }
            return false;
        };
        
        int best = INT_MAX;
        int bv = 0;
        for (int b = 0; b < (1 << target.size()); ++b) {
            bool conflict = false;
            for (const auto & s : dictionary) {
                if (s.size() != target.size()) {
                    continue;
                }
                if (check(b, s)) {
                    continue;
                }
                conflict = true;
                break;
            }
            if (!conflict) {
                int l = 0;
                int skip = 0;
                for (int i = 0; i < target.size(); ++i) {
                    if (b & (1 << i)) {
                        if (skip != 0) {
                            l += skip < 10 ? 1 : 2;
                        }
                        skip = 0;
                        l++;
                    } else {
                        skip++;
                    }
                }
                if (skip != 0) {
                    l += skip < 10 ? 1 : 2;
                }
                if (l < best) {
                    best = l;
                    bv = b;
                }
            }
        }
        
        string ret;
        int skip = 0;
        for (int i = 0; i < target.size(); ++i) {
            if (bv & (1 << i)) {
                if (skip != 0) {
                    ret += to_string(skip);
                }
                skip = 0;
                ret.push_back(target[i]);
            } else {
                skip++;
            }
        }
        if (skip != 0) {
            ret += to_string(skip);
        }
        return ret;
    }
};
