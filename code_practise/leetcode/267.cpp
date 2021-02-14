class Solution {
    void gen(deque<char> &remain, string &sofar, int n, vector<string> *output) {
        if (n == sofar.size()) {
            output->push_back(sofar);
        }
        int size = remain.size();
        char lastChar = 0;
        for (int i = 0; i < size; ++i) {
           if (remain.front() == lastChar) {
               remain.push_back(remain.front());
               remain.pop_front();
               continue;
           } 
            
           lastChar = remain.front();
           remain.pop_front();
           sofar.push_back(lastChar);
            
           gen(remain, sofar, n, output);
            
           remain.push_back(sofar.back());
           sofar.pop_back();
        }
    }
public:
    vector<string> generatePalindromes(string s) {
        unordered_map<char, int> refcount;
        for (int i = 0; i < s.size(); ++i) {
            refcount[s[i]]++;
        }
        
        bool found = true;
        char center = 0;
        if (s.size() % 2 == 1) {
            found = false;
        }
        
        deque<char> remain;
        for (auto pr : refcount) {
            if (pr.second % 2 == 1) {
                if (found) {
                    return {};
                } else {
                    center = pr.first;
                    found = true;
                }
            }
            for (int i = 0; i < pr.second / 2; ++i) {
                remain.push_back(pr.first);
            }
        }
        
        sort(remain.begin(), remain.end());
        vector<string> output;
        int n = s.size() / 2;
        string sofar;
        gen(remain, sofar, n, &output);
        for (auto & s : output) {
            string tail = s;
            reverse(tail.begin(), tail.end());
            if (center != 0) {
                s.push_back(center);
            }
            s = s + tail;
        }
        
        return output;
    }
};