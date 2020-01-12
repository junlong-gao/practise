auto f = []() {
    std::ios::sync_with_stdio(false);cin.tie(NULL); return 0;
}();
class Solution {
public:
    int distinctEchoSubstrings(string text)
    {
        unordered_set<string_view> ss;
        for(int i = 1; i <= text.size() / 2 + 1; i++) {
            int l = 0, r = i, c = 0;
            while(r < text.size()) {
                if(text[l++] == text[r++]) {
                    c++;
                } else  {
                    c = 0;
                }
                
                if(c >= i) {
					ss.insert(string_view(text.c_str() + l, i));
                }
            }
        }
        return ss.size();
    }
};
