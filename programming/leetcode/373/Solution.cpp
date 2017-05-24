#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <queue>
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
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto heap_comp = [&](const pair<int, int>& l, const pair<int, int>& r){
            return nums1[l.first] + nums2[l.second] > nums1[r.first] + nums2[r.second];
        };
        priority_queue<pair<int,int>, vector<pair<int, int>>, decltype(heap_comp)> heap(heap_comp);
        for(int i = 0; i < min((int)nums1.size(), k); ++i){
            if(!nums2.empty()) heap.emplace(i, 0);
        }
        vector<pair<int, int>> ret;
        for(int i = 0; i < k && !heap.empty(); ++i){
            auto top = heap.top();
            ret.emplace_back(nums1[top.first], nums2[top.second]);
            heap.pop();
            if(top.second + 1 < nums2.size()){
                heap.emplace(top.first, top.second+1);
            }
        }
        
        return ret;
    }
};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


