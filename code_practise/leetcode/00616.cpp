class Solution {
public:
    string addBoldTag(string s, vector<string>& dict) {
	string ret;
	vector<int> ext;
	
	ext.resize(s.size(), 0);
	for (const auto &ss : dict) {
		/*
for every word in dict, ext[i] will be word.size() for all i that matches word

find a prefix.
for every char in range (1, end + 1), try to extend this prefix.
until reach the end of string

                       */
		size_t pos = 0;
		while (pos < s.size()) {
		pos = s.find(ss, pos);
		if (pos != std::string::npos) {
			ext[pos] = max(ext[pos], (int)ss.length());
			pos++;
		} else {
			break;
		}
		}
	}

	for (int i = 1; i < s.size(); ++i) {
		ext[i] = max(ext[i], ext[i-1] - 1);
	}

	int idx = 0;
	while (idx < ext.size()) {
		int start = idx;
		while (idx < ext.size() && ext[idx] > 0) { idx++;}
		if (idx - start > 0) {
			ret += "<b>";
			ret += s.substr(start, idx - start);
			ret += "</b>";
		}
		start = idx;
		while (idx < ext.size() && ext[idx] == 0) { idx++; }
		if (idx - start > 0) {
			ret += s.substr(start, idx - start);
		}
	}
	return ret;
    }
};
