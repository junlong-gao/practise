//
// Created by Junlong Gao on 8/7/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include "catch.hpp"
#include <vector>
namespace lee162{
	using namespace std;

	class Solution {
	public:
		int findPeakElement(vector<int>& nums) {
			int i, j, m;
			i = 0; j = nums.size() - 1;
			while(i < j){
				m = i + (j - i) /2;
				int p = nums[m];
				if((m + 1 <= j && nums[m+1] < p) || (m+1>j)){
					if(m == i || nums[m - 1] < p) return m;
					j = m;
				} else{
					i = m + 1;
				}
			}
			return i;
		}
		int findPeakElement(vector<int>&& nums) { //make test suite happy
			return this->findPeakElement(nums);
		}
	};

	TEST_CASE( "test suite for 162 1", "[162 1]" ) {
		Solution testObj;
		REQUIRE( testObj.findPeakElement({1,2,1}) == 1 );
	}
	TEST_CASE( "test suite for 162 2", "[162 2]" ) {
		Solution testObj;
		REQUIRE( testObj.findPeakElement({1,2,3}) == 2 );
	}
	TEST_CASE( "test suite for 162 3", "[162 3]" ) {
		Solution testObj;
		REQUIRE( testObj.findPeakElement({3,2,1}) == 0 );
	}
}
#endif //PRACTISE_SOLUTION_H
