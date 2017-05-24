#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;

    class Solution {
        class UF{
            int counter;
            vector<int> p, rank;
        public:
            UF(int n){
                counter = 0;
                p.resize(n, -1);
                rank.resize(n, 0);
            }
            bool isIsland(int n){
                return p[n] != -1;
            }
            void add(int n){
                p[n] = n;
                counter++;
            }
            bool connected(int x, int y){
                return find(x) == find(y);
            }
            int find(int n){
                int pn = p[n];
                while(n != p[n]){
                    p[n] = p[p[n]];
                    n = p[n];
                }
                return n;
            }
            void union_ele(int x, int y){
                int nx = find(x);
                int ny = find(y);
                counter --;
                if(rank[nx] > rank[ny]){
                    p[ny] = nx;
                }else{
                    p[nx] = ny;
                    if(p[nx] == p[ny]){
                        rank[ny]++;
                    }
                }
            }
            int count(){
                return counter;
            }
        };
        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, 1, 0, -1};
        int n, m;
        int marshall(int x, int y){
            return x * n + y;
        }
        bool valid(int x, int y, UF& uf){
            if( x < 0 || x >= m) return false;
            if( y < 0 || y >= n) return false;
            if(!uf.isIsland(marshall(x, y))) return false;
            return true;
        }
    public:
        vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
            UF uf(n*m);
            vector<int> rst;
            this->n = n;
            this->m = m;
            for(auto& pr : positions){
                int x = pr.first, y = pr.second;
                uf.add(marshall(x,y));
                for(int i = 0; i < 4; ++i){
                    int nx = x + dx[i], ny = y + dy[i];
                    if(valid(nx, ny, uf) && !uf.connected(marshall(x, y), marshall(nx, ny))){
                        uf.union_ele(marshall(x,y), marshall(nx,ny));
                    }
                }
                rst.push_back(uf.count());
            }
            return rst;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
        
        SECTION("sample"){
            vector<pair<int, int>> test{
                {0,0},{0,1},{1,2},{2,1}
            };
            auto rst = testObj.numIslands2(3, 3, test);
            vector<int> expected{1,1,2,3};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
        }
        
         
        SECTION("runtime error"){
            vector<pair<int, int>> test{
                {0,0},{1,1},{0,1}
            };
            auto rst = testObj.numIslands2(2, 2, test);
            vector<int> expected{1,2,1};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
            
        }
        
        SECTION("runtime error"){
            vector<pair<int, int>> test{
                {7,0}
            };
            auto rst = testObj.numIslands2(8, 2, test);
            vector<int> expected{1};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
            
        }
        SECTION("wa"){
            vector<pair<int, int>> test{
                {0,1},{1,2},{2,1},{1,0},{0,2},{0,0},{1,1}
            };
            auto rst = testObj.numIslands2(3, 3, test);
            vector<int> expected{1,2,3,4,3,2,1};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
            
        }
        
    }
}


