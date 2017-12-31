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
	// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
	class Iterator {
		vector<int> data;
		int idx;
	public:
		Iterator(const vector<int>& nums){
			data = nums;
			idx = 0;
		}
		// Returns the next element in the iteration.
		int next(){
			return data[idx++];
		}
		// Returns true if the iteration has more elements.
		bool hasNext() const{
			return idx < data.size();
		}
	};


	class PeekingIterator : public Iterator {
		int cache;
		bool has_next;
	public:
		PeekingIterator(const vector<int>& nums) : Iterator(nums) {
			// Initialize any member here.
			// **DO NOT** save a copy of nums and manipulate it directly.
			// You should only use the Iterator interface methods.
			if(Iterator :: hasNext()){
				cache = Iterator :: next();
				has_next = true;
			}else{
				has_next = false;
			}
		}

		// Returns the next element in the iteration without advancing the iterator.
		int peek() {
			return cache;
		}

		// hasNext() and next() should behave the same as in the Iterator interface.
		// Override them if needed.
		int next() {
			int ret = cache;
			if(Iterator::hasNext()){
				cache = Iterator::next();
				has_next = true;
			}else{
				has_next = false;
			}
			return ret;
		}

		bool hasNext() const {
			return has_next;
		}
	};

	TEST_CASE("tests 1"){
		PeekingIterator testObj({1,2,3,4});
		SECTION("sample") {
            REQUIRE(testObj.peek() == 1);
            REQUIRE(testObj.next() == 1);
            REQUIRE(testObj.peek() == 2);
        }
	}
    TEST_CASE("tests 2"){
        PeekingIterator testObj({1,2,3,4});
        SECTION("sample") {
            REQUIRE(testObj.next() == 1);
            REQUIRE(testObj.next() == 2);
            REQUIRE(testObj.next() == 3);
            REQUIRE(testObj.peek() == 4);
            REQUIRE(testObj.hasNext());
            REQUIRE(testObj.next() == 4);
            REQUIRE(!testObj.hasNext());
        }
    }
}


