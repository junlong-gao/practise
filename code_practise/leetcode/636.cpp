class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> ret(n, 0);
        vector<pair<int, int>> cs; // id, last start time
        for (auto &s : logs) {
            int i = 0, j = 0;
            while (j < s.length() && isdigit(s[j])) {
                j++;
            }
            int id = stoi(s.substr(i, j - i));
            assert(s[j] == ':'); j++; i = j;
            while (j < s.length() && s[j] != ':') {
                j++;
            }
            string state = s.substr(i, j - i);
            assert(s[j] == ':'); j++; i = j;
            while (j < s.length() && isdigit(s[j])) {
                j++;
            }
            int ts = stoi(s.substr(i, j - i));
            if (state == "start") {
               if (cs.size()) {
                  ret[cs.back().first] += ts - cs.back().second;
               }   
               cs.push_back(make_pair(id, ts));
            } else {
                ret[cs.back().first] += ts + 1 - cs.back().second;
                cs.pop_back();
                if (cs.size()) {
                    cs.back() = make_pair(cs.back().first, ts + 1);
                }
                
            }
        }
        
        return ret;
    }
};
