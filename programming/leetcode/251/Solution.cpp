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
    class Vector2D {
        vector<vector<int>>& data;
        int x, y;
    public:
        Vector2D(vector<vector<int>>& vec2d):data(vec2d) {

        }

        int next() {
            while(x < data.size() && data[x].empty()) {x++; y = 0;}
            int ret = data[x][y];
            y++;
            if(y == data[x].size()){
                y = 0; x++;
            }
            return ret;
        }

        bool hasNext() {
            while(x < data.size() && data[x].empty()) {x++; y = 0;}
            if(x >= data.size()) return false;
            if(y >= data[x].size()) return x!=data.size() - 1;
            return true;
        }
    };
	/*
	TEST_CASE("tests"){
		Vector2D testObj;
		SECTION("sample"){

		}
	}
	*/
}


