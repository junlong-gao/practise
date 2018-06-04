class Solution {
public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        vector<unordered_map<char, int>> wordsHash;
	for (const auto& s : words) {
		wordsHash.emplace_back();
		for (char c : s) {
			wordsHash.back()[c]++;
		}
	}
	string best;
	unordered_map<char, int> sig;
	for (char c : licensePlate) {
		if (!isalpha(c)) continue;
		sig[tolower(c)]++;
	}

	for (int i = 0; i < words.size(); ++i) {
		bool match = true;
		for (auto pr : sig) {
			if (pr.second > wordsHash[i][pr.first]) {
				match = false; break;
			}
		}
		if (match) {
			if (best.empty() || best.length() > words[i].length()) {
				best = words[i];
			}
		}
	}
	return best;
    }
};

