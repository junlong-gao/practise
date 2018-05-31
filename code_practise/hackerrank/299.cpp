class Solution {
public:
    string getHint(string secret, string guess) {
            array<int, 10> secretMap;
	for (int i  = 0; i < 10; ++i) {
		secretMap[i] = 0;
	}
	int bull = 0, cow = 0;
	for (int i = 0; i < guess.size(); ++i) {
		if (secret[i] == guess[i]) {
			bull++;
		} else {
			if (++secretMap[secret[i] - '0'] <= 0) { cow++;}
			if (--secretMap[guess[i] - '0'] >= 0) { cow++; }
		}
}
	return to_string(bull) + "A" + to_string(cow) + "B";
    }
};
/*
1234
4443
balance sheet technique:
if we see a char in secret, balance ++
if we see a char in guess, balance --;
if we find after secret ++, balance <= 0, that means the balance cancelled out with a previous guess
if we find after guess --, balance >= 0, that means the balance cancelled out with a previous secret.
*/

