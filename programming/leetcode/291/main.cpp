#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"

using namespace std;
class Solution {
    unordered_map<char, string>  s;
    unordered_set<string> used;
    string pattern, str;
    int size, psize;
public:
    bool dfs(int cur, int p){
        if(cur > size || p > psize) return false;
        if(cur == size && p == psize){
            return true;
        }else{
            auto it = s.find(pattern[p]);
            if(it == s.end()){
                for(int j = 1; j <= size - cur; ++j){
                    auto t = str.substr(cur, j);
                    s[pattern[p]] = t;
                    auto id = used.find(t);
                    if(id == used.end()){
                        used.insert(t);
                        if(dfs(cur + j, p + 1)) return true;
                        used.erase(t);

                    }
                    s.erase(pattern[p]);
                }
                return false;
            }else{
                auto& par = it->second;
                //cerr << cur << "  " << p << " " <<  par << endl;
                if(str.substr(cur, par.length()) == par){
                    return dfs(cur + par.length(), p + 1);
                }else{
                    return false;
                }
            }
        }
    }
    bool wordPatternMatch(string pattern, string str) {
        this->pattern = pattern;
        this->str = str;
        this->size = str.size();
        this->psize = pattern.size();
        return dfs(0,0);
    }
};

int main(){
    std::ifstream in(FILENAME);
    if(DEBUG){
        std::cin.rdbuf(in.rdbuf());
    }
    Solution s;
    string pattern = "aaaa"; 
    string str = "asdasdasdasd";
    bool rst = s.wordPatternMatch(pattern, str);
    cout << (rst ? "YES" : "NO") << endl;
    return 0;
}
