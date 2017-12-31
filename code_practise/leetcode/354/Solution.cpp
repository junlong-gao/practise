#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
	class Solution {
		using pr = pair<int, int>;
	public:
		int maxEnvelopes(vector<pair<int, int>>& envelopes) {
			if(envelopes.size() == 0) return 0;
			sort(envelopes.begin(), envelopes.end(), [&](const pr& l, const pr& r){
				if(l.first != r.first) return l.first< r.first;
				return l.second > r.second;
			});
			int n = envelopes.size();
			//key idea: look, we just need a longest increasing subsequence in height!
			vector<int> dp;
			for(int i = 0; i < n; i++){
				int h = envelopes[i].second;
				auto it = lower_bound(dp.begin(), dp.end(), h);
				if(it!=dp.end()){
					*it = h;
				}else{
					dp.push_back(h);
				}
			}
			return dp.size();
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


