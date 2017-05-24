#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <queue>
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
class Solution {
    bool dfs(double& so_far, string cur, string& t, 
        unordered_map<string, unordered_map<string, double>>& g,
        unordered_map<string, bool>& mask){
        if(cur == t) return true;
        for(auto& n : g[cur]){
            if(!mask[n.first]){
                mask[n.first] = true;
                so_far *= g[cur][n.first];
                if(dfs(so_far, n.first, t, g, mask)) return true;
                so_far /= g[cur][n.first];
                mask[n.first] = false;
            }
        }
        return false;
    }
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, unordered_map<string, double>> g;
        unordered_map<string, bool> mask;
        for(int i = 0; i < values.size(); ++i){
            auto& pr = equations[i];
            g[pr.first][pr.second] = values[i];
            g[pr.second][pr.first] = 1.0/values[i];
            mask[pr.first] = mask[pr.second] = false;
        }
        vector<double> ret;
        for(auto& q: queries){
            string& s = q.first, &e = q.second;
            double rst = 1;
            if(mask.find(s) != mask.end() && dfs(rst, s, e, g, mask)) ret.push_back(rst);
            else ret.push_back(-1);
            for(auto& pr : mask){
                pr.second = false;
            }
        }
        return ret;
    }
};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


