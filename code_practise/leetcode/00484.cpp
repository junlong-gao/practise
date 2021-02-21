/*
DI
2 1 3

3 2 1
D D

D I D D I D
0 -1 0 -1 -2 -1 -2

D
2 1

D I
2 1 3
D D
3 2 1
I D
1 3 2
I I
1 2 3

D I         D I
1 2 3 -> 2 1 3

D D
1 2 3 -> 2 1 3 -> 2 3 1
*/

/*
Digestion
For problems involves permutation, usually it is done over an existing seq [1...n]
For regions all 'I', that region can remain the same
For region all 'D', that region can be a reverse of the original region
If you have I's followed by D's, you can still use tactic 2 and 3 to glue two regions, and is the smallest permutation
If you have D's followed by I's, you can still use tactic 3 and 2 to glue two regions, and is the smallest permutation
The construct is lex smallest, because every string can be decomposed into these regions, then induction by regions.
*/

class Solution {
public:
    vector<int> findPermutation(string s) {
        int n = s.size() + 1;
        vector<int> ret;
	for (int i = 1; i <= n; ++i) {
		ret.push_back(i);
	}
	for (int i = 0; i < s.size(); ++i) {
		int j = i;
		while (j < s.size() && s[j] == 'D') j++;
		reverse(ret.begin() + i, ret.begin() + j + 1); // D D I
		i = j;
	}
 	return ret;
    }
};

