//
//  main.cpp
//  Course Schedule II
//
//  Created by John on 9/12/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>
#include <utility>      // std::pair
#include <unordered_set>

using namespace std;

class Solution {
public:
    
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<unordered_set<int>> G(numCourses);
        vector<int> unvisited(numCourses,0);
        vector<int> rst;
        
        for (int i=0; i<prerequisites.size(); ++i){
            G[prerequisites[i].second].insert(prerequisites[i].first);
        }
        
        for (int i = 0; i<numCourses; i++) {
            if(!DFS(i, G, unvisited, rst)){ //it's kinda funny if we add unvisited[i]==0 as a pre condition
                rst.clear();
                return rst;
            }
        }
        
        reverse(rst.begin(), rst.end());
        return rst;
    }
    
    bool DFS(int i, vector<unordered_set<int>>& G, vector<int>& unvisited,vector<int>& rst){
        
        if (unvisited[i]==-1) {
            return false;//ok we have a cycle
        }
        
        if (unvisited[i]==1) {
            return true;//ok this we have visited, die this path
        }
        
        unvisited[i]=-1;//mark a grey;
        for (auto j:G[i]) {
            if(!DFS(j, G, unvisited, rst)){
                //we have a cycle, popping out the stack frame
                return false;
            }
        }
        
        rst.push_back(i);
        unvisited[i]=1;
        return true;
    }
};
int main(int argc, const char * argv[]) {
    vector<pair<int, int>> prerequisites;
    int numCourses = 7;
    prerequisites.push_back(make_pair(1, 0));
    prerequisites.push_back(make_pair(2, 0));
    prerequisites.push_back(make_pair(3, 1));
    prerequisites.push_back(make_pair(3, 2));
    prerequisites.push_back(make_pair(5, 4));
    prerequisites.push_back(make_pair(6, 5));
    //prerequisites.push_back(make_pair(4, 6));

    Solution mysolutions;
    auto rst = mysolutions.findOrder(numCourses, prerequisites);
    
    for (auto i = 0; i<rst.size(); i++) {
        cout<<rst[i]<<" ";
    }
    return 0;
}
