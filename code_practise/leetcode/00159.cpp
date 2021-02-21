class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int k = 2;
        int cur = 0, tail = -1;
        int best = 0;
        list<pair<int, char>> q;
        unordered_map<char, list<pair<int, char>>::iterator> bag;
        // init
        while (cur < s.size() && q.size() < k) {
            if (bag.count(s[cur]) == 1) {
                q.erase(bag[s[cur]]);
                bag.erase(s[cur]);
            }
            
            q.push_front({cur, s[cur]});
            bag[s[cur]] = q.begin();
            
            best = max(best, cur - tail);
            
            cur++;
        }
        
        // scan
        while (cur < s.size()) {
            assert(q.size() == k);
            
            if (bag.count(s[cur]) == 1) {
                q.erase(bag[s[cur]]);
                bag.erase(s[cur]);
            } else { // k > 0
                tail = q.back().first;
                bag.erase(q.back().second);
                q.pop_back();
            }
            
            q.push_front({cur, s[cur]});
            bag[s[cur]] = q.begin();
            best = max(best, cur - tail);
            
            cur++;
                
            assert(q.size() == k);
        }
        
        return best;        
    }
};