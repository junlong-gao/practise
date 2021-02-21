class Solution {
	int l = 0;
	vector<bool> bits;
	bool get(int i) {
		return bits[i];
	}
	void set(int i) {
		bits[i] = true;
	}
	void clear(int i) {
		bits[i] = false;
	}
	bool f() {
		for (int i = 0; i + 1 < l; ++i) {
			if (get(i) && get(i + 1)) {
				clear(i); clear(i + 1);
				bool ret = f();
				set(i); set(i + 1);

				if (ret == false) {
					return true;
				}
			}
		}
		return false;
	}
public:
    bool canWin(string s) {
	l = s.length();
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '+') bits.push_back(true);
		else bits.push_back(false);
	}
	return f();
    }
};
/*
Derive your algorithm runtime complexity.
O((n - 2) * (n - 4) * ...)
extra: Sprague-Grundy Theorem
*/
