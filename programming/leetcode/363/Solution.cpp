#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>


namespace{
	using namespace std;

	class Solution {
    public:
        int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
            int cur_max = numeric_limits<int>::min();
            for(int l = 0; l < matrix[0].size(); ++l){
                vector<int> sum(matrix.size(), 0);
                for(int r = l; r < matrix[0].size(); ++r){
                    for(int i = 0; i < matrix.size(); ++i){
                        sum[i] = sum[i] + matrix[i][r];
                    }
                    set<int> hist;
                    hist.insert(0);
                    int cur = 0;
                    for(int i = 0; i < matrix.size(); ++i){
                        cur += sum[i];
                        auto it = hist.lower_bound(cur - k);
                        if(it != hist.end()){
                            cur_max = max(cur_max, cur - *it);
                        }
                        hist.insert(cur);
                    }
                }
            }
            return cur_max;
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


