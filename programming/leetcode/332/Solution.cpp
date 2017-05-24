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
        using g_t = unordered_map<string, vector<string>>;
        using mask_t = unordered_map<string, vector<bool>>;

        int edges = 0;
        g_t graph;
        mask_t mask;

        vector<string> bucket;
        bool dfs(string current){
            //cout << "at " << current << endl;
            if(edges == 0) return true;
            auto& dests = graph[current];
            for(int i = 0; i < dests.size(); ++i){
                if(mask[current][i]){
                    mask[current][i] = false;
                    edges--;
                    bucket.push_back(dests[i]);
                    if(dfs(dests[i])) return true;
                    bucket.pop_back();
                    mask[current][i] = true;
                    edges++;
                }
            }
            return false;
        }
    public:
        vector<string> findItinerary(vector<pair<string, string>> tickets) {
            for(auto& ticket : tickets){
                graph[ticket.first].push_back(ticket.second);
                edges++;
            }
            for(auto& edges: graph){
                sort(edges.second.begin(), edges.second.end());
                mask[edges.first].resize(edges.second.size(), true);
            }
            bucket.push_back("JFK");
            dfs("JFK");
            return bucket;
        }
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


