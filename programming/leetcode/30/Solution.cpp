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
    class Solution { //slow but works, need refinement
    public:
        vector<int> findSubstring(string s, vector<string>& words) {
            if(words.empty() || words[0].length() > s.length()) return {};
            
            unordered_map<string, int> table;
            for(auto& word:words){
                table[word]++;
            }
            unordered_map<string, int> copy = table;
            vector<int> rst;
            int size = words[0].length();
            int i = 0;
            int j = i;
            int tofind = words.size();
            while(i < s.length()){
                int t = j;
                while(j < s.length() && j - i < size*(words.size() - tofind + 1)) j++;
                if(j - t < size) break;
                string probe = s.substr(j - size, size);
                if(copy.find(probe) != copy.end()){
                    copy[probe]--;
                    tofind--;
                    if(copy[probe] == 0){
                        copy.erase(probe);
                        if(tofind == 0){
                            copy = table;
                            rst.push_back(i);
                            tofind = words.size();
                            i++; j = i;
                        }
                    }
                    
                }else{
                    copy = table;
                    tofind = words.size();
                    i++; j = i;
                }
            }
            return rst;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){

		}
	}
}


