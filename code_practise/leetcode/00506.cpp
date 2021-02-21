class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        	vector<int> inv(nums.size());
	for (int i = 0; i < nums.size(); ++i) {
		inv[i] = i;
	}
	sort(inv.begin(), inv.end(), [&](int l, int r) {
		return nums[l] > nums[r];
	});
    vector<int> rank(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
        rank[inv[i]] = i;
    }
	vector<string> ret;
	for (int i = 0; i < rank.size(); ++i) {
		if (rank[i] == 0) {
			ret.push_back("Gold Medal");
		} else if (rank[i] == 1) {
			ret.push_back("Silver Medal");
		} else if (rank[i] == 2) {
			ret.push_back("Bronze Medal");
		} else {
			ret.push_back(to_string(rank[i] + 1));
		}
	}
	return ret;
    }
};



