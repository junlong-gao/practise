class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> ret;
        for (auto op : ops) {
            if (op == "+") {
                auto l = ret.back();
                auto r = ret[ret.size() - 2];
                ret.push_back(l + r);
            } else if (op == "D") {
                ret.push_back(ret.back() * 2);
            } else if (op == "C") {
                ret.pop_back();
            } else {
                ret.push_back(stoi(op));
            }
        }
        
        int res = 0;
        for (auto v : ret) {
            res += v;
        }
        return res;
    }
};