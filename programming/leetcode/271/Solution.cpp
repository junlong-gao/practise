#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <sstream>


namespace{
	using namespace std;
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
    class Codec {
    public:
        
        // Encodes a list of strings to a single string.
        string encode(vector<string>& strs) {
            string code;
            for(auto& str: strs){
                code += to_string(str.size());
                code += "\n";
                for(int i = 0; i < str.size(); ++i){
                    int c = str[i];
                    code += to_string(c);
                    code += "\n";
                }
            }
            cout << code << endl;
            return code;
        }
        
        // Decodes a single string to a list of strings.
        vector<string> decode(string s) {
            istringstream out(s);
            vector<string> output;
            int size;
            while(out >> size){
                string t;
                for(int i = 0; i < size; ++i){
                    int c;
                    out >> c;
                    char val = c;
                    t += val;
                }
                output.push_back(t);
            }
            return output;
        }
    };
    
    TEST_CASE("tests"){
		Codec testObj;
		SECTION("sample"){
            vector<string> cases{"11asad", "wadaw\n\t"};
            auto rst = testObj.decode(testObj.encode(cases));
            for(int i = 0; i < cases.size(); ++i){
                REQUIRE(rst[i] == cases[i]);
            }
		}
	}
}


