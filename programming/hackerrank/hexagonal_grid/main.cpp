#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[12][12];
int N;
string s1, s2; 

bool search(int l, int r){
    if(l < 0 || r < 0) return 0;
    if(l == 0 && r == 0) return 1;

    if(l == 0 && r > 0 && s2[r - 1] == '1')
        return search(l, r-1);

    if(l > 0 && r == 0 && s1[l-1] == '1')
        return search(l-1, r);
    if(dp[l][r] != -1) return dp[l][r];
    int rst = 0;
    if(s1[l-1] == '1')
        rst |= search(l-1,r);
 
    if(s2[r-1] == '1')
        rst |= search(l,r-1);

    if(r > 1 && s2[r-1]== '0' && s2[r-2] == '0')
        rst |= search(l, r-2);

    if(l > 1 && s1[l-1]== '0' && s1[l-2] == '0')
        rst |= search(l-2, r);
    
    if(l == r && s1[l - 1] == '0' && s2[r - 1] =='0')
        rst |= search(l - 1, r - 1);
  
    if(l == r + 1 && s1[l - 1] == '0' && s2[r - 1] =='0')
        rst |= search(l - 1, r - 1);
    dp[l][r] = rst;
    return rst;
    

}

int main() {
    int T; cin >> T;
    while(T--){
        memset(dp, -1, sizeof(dp));
        cin >> N >> s1 >>s2;
        cout << ((search(N,N) == 1)? "YES":"NO") << endl;


    }
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}

