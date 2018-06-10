class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        	vector<int> ranks(nums.size());
	sort(ranks.begin(), ranks.end(), [&](int l, int r) {
		return nums[l] < nums[r];
	});
	vector<string> ret;
	for (int i = 0; i < ranks.size(); ++i) {
		if (i == 0) {
			ret.push_back("Gold Medal");
		} else if (i == 1) {
			ret.push_back("Silver Medal");
		} else if (i == 2) {
			ret.push_back("Bronze Medal");
		} else {
			ret.push_back(to_string(ranks[i]));
		}
	}
	return ret;
    }
};


