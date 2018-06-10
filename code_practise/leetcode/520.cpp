class Solution {
public:
    bool detectCapitalUse(string word) {
	int last = -1; int count = 0;
        	for (int i = 0; i < word.size(); ++i) {
		if (std::isupper(word[i])) {
			last = i; count++;
		}
	}
	if (last == -1) return true;
	if (count == 1) return last == 0;
	return count == word.size();
    }
};


