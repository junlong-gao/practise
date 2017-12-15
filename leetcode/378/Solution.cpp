#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <queue>
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
	    int kthSmallest(vector<vector<int>>& matrix, int k) {
		auto heap_comp = [&](const pair<int, int>& l, const pair<int, int>& r){
		    return matrix[l.first][l.second] > matrix[r.first][r.second];
		};
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(heap_comp)> heap(heap_comp);
		for(int i = 0; i < matrix.size(); ++i){
		    heap.emplace(i, 0);
		}
		int rst = 0;
		for(int i = 0; i < k; ++i){
		    auto top = heap.top();
		    //cout << matrix[top.first][top.second] << endl;
		    rst = matrix[top.first][top.second];
		    heap.pop();
		    top.second++;
		    if(top.second < matrix[top.first].size()){
			heap.push(top);
		    }
		}
		return rst;

	    }
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


