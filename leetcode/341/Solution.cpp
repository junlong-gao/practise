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
	/*
	class NestedIterator {
		vector<NestedInteger> s;
	public:
		NestedIterator(vector<NestedInteger> &nestedList){
			while(!nestedList.empty()){
				s.push_back(nestedList.back());
				nestedList.pop_back();
			}
		}

		int next() {
			int ret = s.back().getInteger();
			s.pop_back();
			return ret;
		}

		bool hasNext() {
			while(!s.empty() && !s.back().isInteger()){
				auto lists = s.back().getList();
				s.pop_back();
				while(!lists.empty()){
					s.push_back(lists.back());
					lists.pop_back();
				}
			}
			return !s.empty();
		}
	};

	TEST_CASE("tests"){
		NestedIterator testObj;
		SECTION("sample"){

		}
	}
	 */
}


