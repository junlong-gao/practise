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
        string simplifyPath(string path) {
            int i = 0;
            vector<string> stack;
            while(i < path.size()){
                int j = i + 1;
                while(j < path.size() && path[j] != '/') ++j;
                if(j - i - 1 == 0){
                    i = j;
                    continue;
                }
                string name = path.substr(i+1, j - i - 1);
                if(name == ".."){
                    if(!stack.empty()){
                        stack.pop_back();
                    }
                }else if (name != "."){
                    stack.push_back(name);
                }
                i = j;
            }
            if(stack.size() == 0) return "/";
            string abs = "";
            for(auto& name: stack){
                abs += "/" + name;
            }
            return abs;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){
            REQUIRE(testObj.simplifyPath("/a/b/..//c/../") == "/a");
		}
	}
}


