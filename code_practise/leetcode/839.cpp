class Solution {
public:
    int numSimilarGroups(vector<string>& A) {
	int gid = 0;
	int count = A.size();
	while(count) {
		deque<string> q;
		for (int i = 0; i < A.size(); ++i) {
			if (A[i] != "") {
				q.push_back(A[i]); 
				A[i] = ""; count--; break;
			}
		}
		gid++;
		while(!q.empty()) {
			auto top = q.front(); q.pop_front();
			for (int i = 0; i < A.size(); ++i) {
				if (A[i] == "") continue;
				vector<int> mis;
				for (int j = 0; j < A[i].size(); ++j) {
					if (A[i][j] != top[j]) {
						mis.push_back(j);
					}
				}
				if (mis.size() == 2 && top[mis[0]] == A[i][mis[1]]
					                 && top[mis[1]] == A[i][mis[0]]) {
					q.push_back(A[i]);
					A[i] = "";
					count--;
				}
			}
		}
	}
	return gid;
    }
};

/*
["jvhpg","jhvpg","hpvgj","hvpgj","vhgjp"]
*/
