class Solution {
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
        unordered_map<int, int> Bm;
	vector<int> ret;
	int n = A.size();
	assert(B.size() == n);

	for (int i = 0; i < n; ++i) {
		Bm[B[i]] = i;
	}

	for (int i = 0; i < n; ++i) {
		ret.push_back(Bm[A[i]]);
	}

	return ret;
    }
};

