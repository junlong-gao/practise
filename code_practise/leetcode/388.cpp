class Solution {
public:
    int lengthLongestPath(string input) {
        vector<pair<int, int>> dirs;
        int i = 0; int curLength = 0; int best = 1;
        
        while (i < input.size()) {
            // start with 0 or more '\t'
            int d = 0;
            while (i < input.size() && input[i] == '\t') {
                i++; d++;
            }
            
            while (dirs.size() && dirs.back().second >= d) {
                curLength -= dirs.back().first;
                dirs.pop_back();
            }
            
            bool isFile = false;
            int start = i;
            while (i < input.size() && input[i] != '\n') {
                if (input[i] == '.') { isFile = true; }
                i++;
            }
            
            if (isFile) {
                best = max(best, curLength + 1 + i - start); // slash
            } else {
                dirs.push_back({1 + i - start, d});
                curLength += dirs.back().first;
            }
            i++; // consume the last '\n'
        }
        
        return best - 1; // first slash does not count
    }
};
