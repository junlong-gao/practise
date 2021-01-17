class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        auto tmp = [](int l, int r) {
            return l > r;
        };
        priority_queue<int, vector<int>, decltype(tmp)> q(tmp);
        for (auto s : sticks) {
            q.push(s);
        }
        int ret = 0;
        while (q.size() >= 2) {
            int news = q.top(); ret += q.top(); q.pop();
            news += q.top(); ret += q.top(); q.pop();
            q.push(news);
        }
        
        return ret;
    }
};