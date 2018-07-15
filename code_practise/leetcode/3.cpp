int x = [&]() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}();

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int m = 1;
        list<pair<char, int>> q;
        unordered_map<char, deque<list<pair<char, int>>::iterator>> bag;
        int cur = 0; int tail = -1;
        int best = 0;
        
        // init
        while (cur < s.length()) {
            char c = s[cur];
            if (bag[c].size() >= m) {
                break;
            } 
            
            q.push_front({c, cur});
            bag[c].push_front(q.begin());
            
            best = max(best, cur - tail);
            cur++;
        }
        
        // update
        while (cur < s.length()) {
            char c = s[cur];
            if (bag[c].size() >= m) {
                tail = bag[c].back()->second;
                auto it = bag[c].back();
                while(it != q.end()) {
                    bag[it->first].pop_back();
                    it = q.erase(it);
                }
            }
                
            q.push_front({c, cur});
            bag[c].push_front(q.begin());
            best = max(best, cur - tail);
            cur++;
        }
        
        return best;
    }
};