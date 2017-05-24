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
    const int maxn = 33;
    int A[maxn];
    bool vis[maxn];
    bool primes[maxn];
    int n, cnt = 0;
    
    void dfs(int cur){
        if(cur == n){
            if(primes[(A[0] + A[n-1])]){
                for(int i = 0; i < n - 1; ++i){
                    cout << A[i] << " ";
                }
                cout << A[n-1] << "\n";
            }
        }else{
            for(int i = 2; i <=n; ++i){
                if(!vis[i] && primes[i+A[cur-1]]){
                    A[cur] = i; vis[i] =true;
                    dfs(cur+1);
                    vis[i] = false;
                }
            }
        }
    }

    void readInput(){
        fill(A, A+n, 0);
        fill(vis, vis+n, false);
        A[0] = 1;
    }
     void run(){
         fill(primes, primes + maxn, true);
         for(int i = 2; i < maxn; ++i){
             if(primes[i]) {
                 for(int j = i * i; j < maxn; j = j+i){
                     primes[j] = false;
                 }
             }
         }
         int kcase = 0;
         while(cin >> n){
             if(kcase > 0) cout << "\n";
             readInput();
             cout << "Case " << ++kcase << ":\n";
             dfs(1);
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
