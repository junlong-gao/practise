#include "catch.hpp"
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


using namespace std;
class Solution {
    int dfs(unordered_map<string, int>& cache, string word, unordered_set<string>& dict){
        if(cache.find(word)!=cache.end()){
            return cache[word];
        }
        int cur_max = 0;
        for(int i = 0; i < word.length(); ++i){
            string probe = word;
            probe.erase(i, 1);
            if(dict.find(probe)!=dict.end()){
                cur_max = max(cur_max, dfs(cache, probe, dict) + 1);
            }
        }
        cache[word] = max(cur_max, cache[word]);
        return cache[word];
    }

    class union_find{
        vector<int> p, rank;
        int num_sets;
    public:
        union_find(int n){
            rank.resize(n, 0);
            for(int i = 0; i < n; ++i){
                p.push_back(i);
            }
            num_sets = n;
        }
        int find(int x){
            while(p[x]!=x){
                p[x] = p[p[x]];
                x = p[x];
            }
            return x;
        }
        bool is_same(int x, int y){
            return find(x) == find(y);
        }
        void unite(int x, int y){
            int px = find(x), py = find(y);
            if(px == py) return;
            if(rank[px] > rank[py]){
                p[py] = px;
            }else{
                p[px] = py;
                if(rank[px] == rank[py]){
                    rank[py]++;
                }
            }
            num_sets--;
        }
        int get_size(){
            return num_sets;
        }
    };

    void search(int u, vector<vector<int>>& g, vector<bool>& mask, union_find& sets){
        for(int i = 0; i < g[u].size(); ++i){
            if(g[u][i] == 1 && mask[i]){
                mask[i] = false;
                sets.unite(u, i);
                search(i, g, mask, sets);
            }
        }
    }
public:
    int longest_chain(unordered_set<string> words){
        unordered_map<string, int> cache;
        int cur_max = 0;
        for(auto& word:words){
            cur_max = max(cur_max, dfs(cache, word, words)+1);
        }
        return cur_max;
    }



    int friend_circle(vector<vector<int>>& friends){
        if(friends.empty()) return 0;
        int n = friends.size();
        union_find sets(n);
        vector<bool> mask(n, true);
        for(int i = 0; i < n; ++i){
            if(mask[i]){
                mask[i] = false;
                search(i, friends, mask, sets);
            }
        }
        return sets.get_size();
    }
};

TEST_CASE("tests"){
    Solution testObj;
    SECTION("sample"){
        unordered_set<string> words = {"a","b","ba","bca", "bda","bdca"};
        REQUIRE(testObj.longest_chain(words) == 4);
    }
    SECTION("friends"){
        vector<vector<int>> grid = {
                {0, 1, 0, 0, 0},
                {1, 0, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 1},
                {0, 0, 0, 1, 0}
        };
        REQUIRE(testObj.friend_circle(grid) == 2);
    }
}



