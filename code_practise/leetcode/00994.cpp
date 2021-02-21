class Solution {
    struct ent_t {
        int count;
        char c;
    };
public:
    string reorganizeString(string S) {
        auto cmp = [](const ent_t &l, const ent_t &r) {
           return l.count < r.count;  
        };
        priority_queue<ent_t, vector<ent_t>, decltype(cmp)> q(cmp);
        unordered_map<char, int> refcount;
        for (auto c : S) {
            refcount[c]++;
        }
        for (auto pr : refcount) {
            q.push(ent_t{pr.second, pr.first});
        }
        
        int count = 0;
        string ret;
        char last = 0;
        while (q.size()) {
            auto top = q.top();
            q.pop();
            if (ret.size() && ret.back() == top.c) {
                return "";
            }
            ret.push_back(top.c);
            top.count--;
            if (q.empty()) {
                if (top.count == 0) {
                    break;
                } else {
                    return "";
                }
            }
            auto secTop = q.top();
            q.pop();
            assert(secTop.c != top.c);
            ret.push_back(secTop.c);
            secTop.count--;
            if (top.count > 0) {
                q.push(top);
            }
            if (secTop.count > 0) {
                q.push(secTop);
            }
        }
        
        return ret;
    }
};
