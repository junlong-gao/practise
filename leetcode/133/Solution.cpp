#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
    struct UndirectedGraphNode {
         int label;
         vector<UndirectedGraphNode *> neighbors;
         UndirectedGraphNode(int x) : label(x) {};
     };
    class Solution {
        unordered_map<int, UndirectedGraphNode*> visited;
        void search(UndirectedGraphNode* node){
            UndirectedGraphNode* clone = new UndirectedGraphNode(node->label);
            visited[node->label] = clone;
            for(auto v : node->neighbors){
                if(visited.find(v->label) == visited.end()){
                    search(v);
                }
                clone->neighbors.push_back(visited[v->label]);
            }
        }
    public:
        UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
            if(node == NULL) return NULL;
            search(node);
            return visited[node->label];
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            UndirectedGraphNode a(0), b(1), c(2);
            a.neighbors.push_back(&b);
            a.neighbors.push_back(&c);
            
            b.neighbors.push_back(&a);
            b.neighbors.push_back(&c);
            
            c.neighbors.push_back(&a);
            c.neighbors.push_back(&b);
            c.neighbors.push_back(&c);
            
            auto clone = testObj.cloneGraph(&a);
            REQUIRE(clone->neighbors[0]->label == 1);
            REQUIRE(clone->neighbors[1]->label == 2);
            
            auto clone_b = clone->neighbors[0];
            auto clone_c = clone->neighbors[1];
            
            REQUIRE(clone_b->neighbors[0]->label == 0);
            REQUIRE(clone_b->neighbors[1]->label == 2);
            
            REQUIRE(clone_c->neighbors[0]->label == 0);
            REQUIRE(clone_c->neighbors[1]->label == 1);
            REQUIRE(clone_c->neighbors[2]->label == 2);

		}
	}
}


