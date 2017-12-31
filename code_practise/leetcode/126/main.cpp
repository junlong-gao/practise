#include <cstdlib>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include <vector>
#include <deque>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string> > findLadders(string start, string end, unordered_set<string> &dict)
    {
        vector<vector<string> > solutions;
        vector<string> ladder;
        ladder.push_back(start);
        unordered_set<string> start_frontier, end_frontier;
        start_frontier.insert(start);
        end_frontier.insert(end);
        unordered_map<string, vector<string> > children;
        
        for (int i = 0; i<26; i++) {
            alphabet[i] = 'a' + i;
        }
        
        if (bidir_bfs(start_frontier, end_frontier, dict, children, true))
            gen_path(start, end, children, ladder, solutions);
        return solutions;
    }
private:
    char alphabet[26];
    
    bool bidir_bfs(unordered_set<string>& start_frontier,
                       unordered_set<string>& end_frontier,
                       unordered_set<string>& dict,
                       unordered_map<string, vector<string> >& children,
                       bool flip)
    {
        flip = !flip;

        if (start_frontier.empty()) {
            return false;
        }
        
        //this will make the code 2 times faster!
        if (start_frontier.size() > end_frontier.size())
            return bidir_bfs(end_frontier, start_frontier, dict, children, flip);
        
        for(auto node:start_frontier){
            dict.erase(node);
        }
        /*
        for(auto node:end_frontier){
            dict.erase(node);
        }
         */
        bool found = false;
        unordered_set<string> new_frontier;
        string curadj;
        for(auto node:start_frontier){
            auto n = node.length();
            curadj = node;
            for (int i = 0; i<n; i++) {
                for (auto c:alphabet) {
                    curadj[i] = c;
                    if (end_frontier.find(curadj)!=end_frontier.end()) {
                        //we have a winner
                        found = true;
                        flip?children[curadj].push_back(node):children[node].push_back(curadj);
                        
                    } else if (dict.find(curadj)!=dict.end()) {
                        new_frontier.insert(curadj);
                        flip?children[curadj].push_back(node):children[node].push_back(curadj);
                    }
                }
                curadj = node;//restore this position
            }
        }
        
        return found || bidir_bfs(end_frontier,new_frontier,dict,children,flip);
    }
    
    void gen_path(string& start,
                    string& end,
                    unordered_map<string, vector<string> >& children,
                    vector<string>& ladder, vector<vector<string> >& solutions) {
        if (start == end) {
            solutions.push_back(ladder);
            return;
        }
        for (string child : children[start]) {
            ladder.push_back(child);
            gen_path(child, end, children, ladder, solutions);
            ladder.pop_back();
        }
    }
};



int main(){
    unordered_set<string> dict;
    vector<string> test;
    string tmp = "hot";
    dict.insert(tmp); test.push_back(tmp);
    tmp = "dog";
    
    dict.insert(tmp); test.push_back(tmp);
    /*
    tmp = "jldk";
    
    dict.insert(tmp); test.push_back(tmp);
    tmp = "oack";
    
    dict.insert(tmp); test.push_back(tmp);
    tmp = "oacd";
    
    dict.insert(tmp); test.push_back(tmp);
    tmp = "oecb";
    
    dict.insert(tmp); test.push_back(tmp);
    tmp = "oafd";
    
    dict.insert(tmp); test.push_back(tmp);
    tmp = "aecb";
    
    dict.insert(tmp); test.push_back(tmp);
    */
    Solution mysolutions;
    //mysolutions.print_ladder(test);
    vector<vector<string> > solutions = mysolutions.findLadders("hot","dog",dict);
    //cout<<"here"<<"\n";
    while(!solutions.empty()){
        auto top = solutions.back();
        for (int i = 0; i<top.size(); i++) {
            cout<<top[i]<<" ";
        }
        cout<<"\n";
        solutions.pop_back();
    }
    return 0;
}