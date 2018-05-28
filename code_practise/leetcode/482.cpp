string licenseKeyFormatting(const string &in, int K) {
	vector<char> cs;
	string ret;
	for (char c : in) {
		if (c == ‘-’) continue;
		if (std::islower(c)) c = c + ‘A’ - ‘a’;
		cs.push_back(c);
	}

	const int n = cs.size();
	const int r = n % K;
	int i = 0;

	while (i < r) {
		ret.push_back(cs[i]);
		i++;
	}
	while (i < n) {
		if (!ret.empty()) ret.push_back(‘-’);
		int j = 0;
		while (j < K) {
			ret.push_back(cs[i]);
			j++; i++;
		}
	}
	return ret;
}
