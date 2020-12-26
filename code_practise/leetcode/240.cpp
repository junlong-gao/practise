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
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int x = 0, y = matrix[0].size() - 1;
        while(x < matrix.size() && y >= 0){
            if(target > matrix[x][y]) x++;
            else if(target < matrix[x][y]) y--;
            else if(target == matrix[x][y]) return true;
        }
        return false;
    }
};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


