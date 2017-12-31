#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <deque>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"

namespace Solution{
    using namespace std;
    int S[27];
    int cnt = 0, n, L;
    bool dfs(int cur){
        if(cnt++ == n){
            for(int i = 0; i < cur; ++i){
                cout << (char)(S[i] + 'A');
            }
            cout << "\n";
            return false;
        }
        for(int i = 0; i < L; ++i){
            S[cur] = i;
            bool ok = true;
            for(int j = 1; 2*j <= cur + 1; ++j){
                bool equal = true;
                for(int k = 0; k < j; ++k){
                    if(S[cur - k] != S[cur - k - j]){
                        equal = false;
                        break;
                    }
                }
                if(equal){ok = false; break;}
            }
            if(ok){
                if(!dfs(cur + 1)) return false;
            }
        }
        return true;
    }
    void run(){
        while(cin >> n >> L && n > 0){
            fill(S, S + 27, 0);
            dfs(0);
        }
    }
}

int main(){
    std::ifstream in(FILENAME);
    if(DEBUG){
        std::cin.rdbuf(in.rdbuf());
    }
    Solution::run();
    return 0;
}
