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
    public:
        int countDigitOne(int n) {
            if(n <= 9){
                return n>=1? 1: 0;
            }
            int exp = 0, t = n;
            while(t > 0){
                t /= 10; exp++;
            }
            exp--;
            int base = pow(10, exp);
            int k = n / base;
            cout << exp << " " << k << " " << base << endl;
            return k*countDigitOne(base - 1) + (k>=1? (k>=2?base:n-base+1): 0) + countDigitOne(n%base);
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            REQUIRE(testObj.countDigitOne(1000) == 301);

		}
	}
}


