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
    using pr = pair<int, int>;
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> rst(n+1, numeric_limits<int>::max());
        vector<int> index(primes.size(), 0);
        int i = 1;
        rst[0] = 1;
        while(i < n){
            for(int j = 0; j < index.size(); ++j){
                rst[i] = min(rst[i], rst[index[j]]*primes[j]);
            }
            for(int j = 0; j < index.size(); ++j){
                index[j] += ((rst[i] == rst[index[j]]*primes[j]) ? 1 : 0);
            }
            ++i;
        }
        return rst[n-1];
    }
};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


