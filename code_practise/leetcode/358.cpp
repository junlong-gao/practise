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
        string rearrangeString(string str, int k) {
            if(k == 0) return str;
            unordered_map<char, int> counts;
            vector<char> chars(26);
            for(char c = 'a'; c <= 'z'; ++c){
                chars[c - 'a'] = c;
            }
            for(int i = 0; i < str.size(); ++i){
                counts[str[i]] ++;
            }
            string out;
            int i = 0;
            while( i < str.length()){
                sort(chars.begin(), chars.end(), [&](const char& l, const char& r){
                    if (counts[l] != counts[r]) return counts[l] > counts[r];
                    return l < r;
                });
                int j = 0;
                while( i < str.length() && j < k ){
                    out += chars[j];
                    if(counts[chars[j]] == 0) return "";
                    counts[chars[j]]--;
                    j++; i++;
                }
            }
            return out;
        }
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


