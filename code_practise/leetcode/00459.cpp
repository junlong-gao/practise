class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        	for (int i = 1; i < s.length(); ++i) {
		if (s.length() % i == 0) {
			bool match = true;
			for (int j = 0; j < s.length(); ++j) {
				if (s[j % i] != s[j]) {
					match = false;
					break;
				}
			}
			if (match) return true;
		}
}
return false;
    }
};


