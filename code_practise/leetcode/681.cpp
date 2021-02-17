class Solution {
public:
    string nextClosestTime(string time) {
        int cur = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
        unordered_set<char> allowed;
        for (auto s : time) {
            allowed.insert(s);
        }
        while (true) {
            cur = (cur + 1) % (24 * 60);
            string ret = to_string(cur / 60 / 10) + to_string(cur / 60 % 10) + ":" + to_string(cur % 60 / 10) + to_string(cur % 60 % 10);
            bool found = true;
            for (auto c : ret) {
                if (allowed.count(c) == 0) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return ret;
            }
        }
    }
};