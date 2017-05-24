#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T; cin >> T;
    while(T--){
        int S; cin >> S;
        string p, q; cin >> p >> q;
        int N = p.length();
        int best  = -1;
        for(int d = -N + 1; d < N; ++d){
            int i, j, l, mismatch;
            i = d < 0 ? 0 : d;
            j = i - d;
            l = 0; mismatch = 0;
            while(i + l < N && j + l < N){
                if(p[i + l] != q[j+l]) mismatch++;
                if(mismatch > S){
                    best = max(best, l);
                    while(p[i] == q[j]){
                        i++; j++; l--;
                    }
                    mismatch--; 
                    i++;j++;
                }else{ //if mismatch is too large, cannot update l
                    l++;
                }
            }
            best = max(best, l);
        }
        cout << best << endl;
    }
    return 0;
}

