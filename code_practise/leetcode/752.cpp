class Solution {
    struct ent_t {
        string n;
        int d;
    };
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> dd;
        for (auto & d : deadends) {
            dd.insert(d);
        }
        if (dd.count("0000")) {
            return -1;
        }
        deque<ent_t> q;
        q.push_back(ent_t{"0000", 0});
        unordered_set<string> visited;
        visited.insert("0000");
        while (q.size()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                const auto top = q.front();
                q.pop_front();
                if (top.n == target) {
                    return top.d;
                }
                string nn = top.n;
                for (int i = 0; i < top.n.size(); ++i) {
                    nn[i] = (top.n[i] - '0' + 1) % 10 + '0';
                    if (dd.count(nn) == 0 && visited.count(nn) == 0) {
                        q.push_back(ent_t{nn, top.d + 1});
                        visited.insert(nn);
                    }
                    nn[i] = (top.n[i] - '0' + 9) % 10 + '0';
                    if (dd.count(nn) == 0 && visited.count(nn) == 0) {
                        q.push_back(ent_t{nn, top.d + 1});
                        visited.insert(nn);
                    }
                    nn[i] = top.n[i];
                }
            }
        }
        return -1;
    }
};
