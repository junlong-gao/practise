/*
//store all nodes (string), each has id
map string -> id
a table represent all edges <id1, id2>
*/
class Solution {
public:
    bool areSentencesSimilar(vector<string>& words1, vector<string>& words2, vector<pair<string, string>> pairs) {
	if (words1.size() != words2.size()) return false;
            unordered_map<string, int> stringToIdx;
	int id = 0;
	for (const auto & pr : pairs) {
		if (stringToIdx.count(pr.first) == 0) {
			stringToIdx[pr.first] = id++;
		}

		if (stringToIdx.count(pr.second) == 0) {
			stringToIdx[pr.second] = id++;
		}
	}

	auto edges {vector<vector<bool>> (id, vector<bool>(id, false))};
	for (const auto & pr : pairs) {
		const int idx1 = stringToIdx[pr.first];
		const int idx2 = stringToIdx[pr.second];
		edges[idx1][idx2] = edges[idx2][idx1] = true;
	}

	for (int i = 0; i < words1.size(); ++i) {
		const string & s1 = words1[i];
		const string & s2 = words2[i];
		if (s1 == s2) continue;
		if (stringToIdx.count(s1) == 0) return false;
 		if (stringToIdx.count(s2) == 0) return false;
		const int idx1 = stringToIdx[s1];
		const int idx2 = stringToIdx[s2];
		if (!edges[idx1][idx2]) return false;
	}

	return true;
    }
};

/*
["great","acting","skills"]
["fine","drama","talent"]
[["great","fine"],["drama","acting"],["skills","talent"]]

["a","b","c"]
["a","d","c"]
[["great","fine"],["drama","acting"],["skills","talent"]]

*/

