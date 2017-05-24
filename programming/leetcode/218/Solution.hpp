#ifndef Solution_hpp
#define Solution_hpp

#include <vector>
#include <set>
#include <functional>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> p;
        vector<pair<int, int>> tmp;
        for(int i = 0; i < buildings.size(); ++i){
            p.push_back({buildings[i][0], buildings[i][2], i});
            p.push_back({buildings[i][1], 0, i});
        }
        sort(p.begin(), p.end(), [&](const vector<int>& l, const vector<int> &r){
            return l[0] < r[0];
        });
        function<bool(int, int)> comp = [&](int l, int r)->bool{
            if(buildings[l][2] != buildings[r][2])
                return buildings[l][2] < buildings[r][2];
            return l < r;
        };
        set<int, decltype(comp)> cps(comp);
        int i = 0;
        while(i < p.size()){
            int x = p[i][0];
            do{ // merge same x points
                auto& ptr = p[i];
                if(ptr[1] > 0 && cps.find(ptr[2]) == cps.end()){ // a new building entering
                    cps.insert(ptr[2]);
                }
                if(ptr[1] == 0 && cps.find(ptr[2]) != cps.end()){ // an existing building leaves
                    cps.erase(ptr[2]);
                }
                i++;
            } while(i<p.size() && p[i-1][0] == p[i][0]);
            
            int h = cps.empty()?0:buildings[*cps.rbegin()][2];
            if(tmp.empty() || tmp.back().second != h){
                tmp.push_back(make_pair(x, h));
            }
        }
        return tmp;
    }
};

#endif /* Solution_hpp */
