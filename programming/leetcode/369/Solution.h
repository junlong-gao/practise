//
// Created by Junlong Gao on 8/7/16.
//

#ifndef PRACTISE_SOLUTION_369
#define PRACTISE_SOLUTION_369
#include<cstdlib>
#include<vector>
namespace{
	using namespace std;

	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(NULL) {}
	};

	class Solution_369 {
	public:
		ListNode* plusOne(ListNode* head) {
			vector<ListNode*> nodes;
			ListNode* cur = head;
			while(cur != NULL){
				nodes.push_back(cur);
				cur = cur->next;
			}
			int carry = 1;
			for(int i = nodes.size() -1 ; i >= 0; --i){
				int rst = (nodes[i]->val + carry);
				carry =  rst/10;
				nodes[i]->val = rst % 10;
			}
			if(carry != 0){
				ListNode* ret = new ListNode(carry);
				ret->next = head;
				return ret;
			}
			return head;
		}
	};

#include "catch.hpp"
	TEST_CASE( "test suite for 369", "[369]" ) {
		Solution_369 testObj;
		ListNode first(1);
		ListNode second(2);  first.next = &second;
		SECTION("no carry case:"){
			ListNode third(3); second.next = &third;
			auto rst = testObj.plusOne(&first);

			REQUIRE(  rst->val == 1 );
			rst = rst->next;
			REQUIRE(  rst->val == 2 );
			rst = rst->next;
			REQUIRE(  rst->val == 4 );
			REQUIRE(  rst->next == NULL );
		}
		SECTION("carry case:"){
			ListNode third(9); second.next = &third;
			auto rst = testObj.plusOne(&first);

			REQUIRE(  rst->val == 1 );
			rst = rst->next;
			REQUIRE(  rst->val == 3 );
			rst = rst->next;
			REQUIRE(  rst->val == 0 );
			REQUIRE(  rst->next == NULL );
		}
		SECTION("add carry case:"){
			ListNode third(9);
			auto rst = testObj.plusOne(&third);

			REQUIRE(  rst->val == 1 );
			rst = rst->next;
			REQUIRE(  rst->val == 0 );
			REQUIRE(  rst->next == NULL );
		}
	}
}

#endif //PRACTISE_SOLUTION_369
