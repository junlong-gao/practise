/*
Digestion:
The flip-flop trick: operations on an interval can be represented using two points: 
   *increase since i and decrease since j + 1*
*/
class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
	vector<int> tmp(length, 0);
	for (int i = 0; i < updates.size(); ++i) {
		tmp[updates[i][0]] += updates[i][2];
/*XXX
		if (updates[i][1] + 1 < updates.size()) {
*/
		if (updates[i][1] + 1 < length) {
			tmp[updates[i][1] + 1] -= updates[i][2];
		}
	}

	int partial = 0;
	for (int i = 0; i < length; ++i) {
		tmp[i] += partial;
		partial = tmp[i];
	}

	return tmp;
    }
};

