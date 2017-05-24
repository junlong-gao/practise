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
		int hours[4] = {1, 2, 4, 8};
		int minutes[6] = {1,2,4,8,16,32};
		vector<int> all_hours;
		vector<int> all_minutes;
		void genHour(int num, int pos, int so_far){
			if(num == 0 && so_far < 12){
				all_hours.push_back(so_far);
			}else{
				for(int i = pos; i < 4; ++i){
					genHour(num - 1, i + 1, so_far + hours[i]);
				}
			}
		}
		void genMin(int num, int pos, int so_far){
			if(num == 0 && so_far < 60){
				all_minutes.push_back(so_far);
			}else{
				for(int i = pos; i < 6; ++i){
					genMin(num - 1, i + 1, so_far + minutes[i]);
				}
			}
		}
	public:
		vector<string> readBinaryWatch(int num) {
			vector<string> rst;
			for(int i = 0; i <= num; ++i){
				genHour(i, 0, 0);
				genMin(num - i, 0, 0);
				for(int j = 0; j < all_hours.size(); ++j){
					for(int k = 0; k < all_minutes.size(); ++k){
						string min = to_string(all_minutes[k]);
						if(min.size() == 1) min = "0" + min;
						rst.emplace_back(to_string(all_hours[j]) +":" + min);
					}
				}
				all_hours.clear();
				all_minutes.clear();
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


