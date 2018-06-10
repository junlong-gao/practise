/*
00011001010110
*/
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        	int old = 0, cur = 0;
	int best = 0;
	for (int i = 0; i < nums.size(); ++i) {
		if (nums[i] == 1) {
			cur++; 
		} else {
			old = cur;
			cur = 0;
		}
		best = max(best, cur + old + 1);
	}
	return best;
    }
};


