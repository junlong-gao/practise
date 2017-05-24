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
        int ret = 0;
        int n, m;
        vector<int> visited;
        void helper(int pos, int k){
            if(k >= m){
                ret ++;
                if(k >= n) return;
            }
            for(int i = 0; i < 9; ++i){
                if(!visited[i] && checker(pos, i)){
                    visited[i] = true;
                    helper(i, k + 1);
                    visited[i] = false;
                }
            }
        }
        bool checker(int pos, int next){
            int coldiff = abs(pos%3 - next%3);
            int rowdiff = abs(pos/3 - next/3);
            if(coldiff == 2 && rowdiff == 2){
                return visited[4];
            }
            if(coldiff == 2 && rowdiff == 0){
                return visited[pos/3 * 3 + 1];
            }
            if(coldiff == 0 && rowdiff == 2){
                return visited[3 + pos%3];
            }
            return true;
        }
    public:
        int numberOfPatterns(int m, int n) {
            this->m = m;
            this->n = n;
            visited.resize(10, false);
            for(int i = 0; i < 9; ++i){
                visited[i] = true;
                helper(i, 1);
                visited[i] = false;
            }
            return ret;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){
            REQUIRE(testObj.numberOfPatterns(1, 1) == 9);
		}
	}
}


