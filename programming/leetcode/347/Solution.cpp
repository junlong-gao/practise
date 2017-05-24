#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
    class Solution {
    public:
        vector<int> topKFrequent(vector<int>& nums, int k) {
            unordered_map<int, int> counts;
            for(int i = 0; i < nums.size(); ++i){
                counts[nums[i]]++;
            }
            vector<unordered_set<int>> buckets(nums.size()+1);
            for(auto& pr : counts){
                buckets[pr.second].insert(pr.first);
            }
            vector<int> rsts;
            int i = nums.size();
            while(i >= 0 && rsts.size() < k){
                if(buckets[i].size() > 0){
                    rsts.push_back(*(buckets[i].begin()));
                    buckets[i].erase(rsts.back());
                }else{
                    --i;
                }
            }
            return rsts;
        }
    };
    TEST_CASE("tests"){
		Solution testObj;
        
		SECTION("sample"){
            vector<int> nums={1,1,1,2,2,3};
            testObj.topKFrequent(nums, 3);
		}
	}
}


