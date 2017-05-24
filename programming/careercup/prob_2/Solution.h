#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <limits>
#include "catch.hpp"
#include "printer.h"

namespace prob_2{
	using namespace std;
	int max_diff(vector<int> arr){
		vector<int> maxleft(arr.size(),0),
				maxright(arr.size(),0), 
				minleft(arr.size(),0),
				minright(arr.size(),0),
				dp(arr.size(), 0);
		int n = arr.size();
		//maxleft:
		dp[0] = maxleft[0] = arr[0];
		for(int i = 1; i < arr.size(); ++i){
			dp[i] = arr[i] + max(0, dp[i-1]);
			maxleft[i] = max(maxleft[i-1], dp[i]);
		}
		LOG(INFO) << sequential::printer(maxleft, 
			[&](int element)->string{
				return to_string(element);
			});

		//minleft:
		dp[0] = minleft[0] = arr[0];
		for(int i = 1; i < arr.size(); ++i){
			dp[i] = arr[i] + min(0, dp[i-1]);
			minleft[i] = min(minleft[i-1], dp[i]);
		}
		LOG(INFO) << sequential::printer(minleft, 
			[&](int element)->string{
				return to_string(element);
			});
		
		//maxright:
		dp[n -1] = maxright[n-1] = arr[n-1];
		for(int i = n - 2; i >=0; --i){
			dp[i] = arr[i] + max(0, dp[i+1]);
			maxright[i] = max(maxright[i+1], dp[i]);
		}
		LOG(INFO) << sequential::printer(maxright, 
			[&](int element)->string{
				return to_string(element);
			});

		//minright:
		dp[n -1] = minright[n-1] = arr[n-1];
		for(int i = n - 2; i >=0; --i){
			dp[i] = arr[i] + min(0, dp[i+1]);
			minright[i] = min(minright[i+1], dp[i]);
		}
		LOG(INFO) << sequential::printer(minright, 
			[&](int element)->string{
				return to_string(element);
			});
		
		int maxdiff = numeric_limits<int>::min();
		for(int i = -1; i < n; ++i){
			int t;
			if(i == -1){
				t = max(abs(maxright[0]),
						abs(minright[0]));	
			}
			if(i>=0 && i < n - 1){
				t = max(abs(maxleft[i] - maxright[i+1]),
						abs(maxright[i+1] - minleft[i]));
			}
			if(i == n-1){
				t = max(abs(maxleft[i]), 
						abs(minleft[i]));
			}
			maxdiff = max(maxdiff, t);
		}
		
		return maxdiff;

	}
	TEST_CASE("max diff smoke"){
		REQUIRE(max_diff({2, -1, -2, 1, -4, 2, 8}) == 16);
	}
}
