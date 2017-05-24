#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
    struct RandomListNode {
        int label;
        RandomListNode *next, *random;
        RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
    };
    class Solution {
    public:
        RandomListNode *copyRandomList(RandomListNode *head) {
            if(head == NULL) return head;
            unordered_map<RandomListNode*, RandomListNode*> clones;
            auto iter = head;
            RandomListNode* clone = new RandomListNode(head->label);
            RandomListNode* clonehead = clone;
            clones[head] = clone;
            while(iter->next){
                clone-> next = new RandomListNode(iter->next->label);
                clone = clone->next;
                iter = iter->next;
                clones[iter] = clone;
            }
            
            iter = head;
            auto clone_iter = clonehead;
            while(iter){
                clone_iter->random = clones[iter->random];
                clone_iter = clone_iter->next;
                iter = iter->next;
            }
            return clonehead;
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            RandomListNode a{1}, b{2}, c{3};
            a.next = &b, b.next = &c;
            a.random = &c; b.random = &a, c.random = &c;
            auto clone = testObj.copyRandomList(&a);
            REQUIRE(clone->label == 1);
            REQUIRE(clone->next->label == 2);
            REQUIRE(clone->next->next->label == 3);
            
            REQUIRE(clone->random->label == 3);
            REQUIRE(clone->next->random->label == 1);
            REQUIRE(clone->next->next->random->label == 3);

		}
	}
}


