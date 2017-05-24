#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n),b(m);
    for(int i =0; i < n; i++){
        cin >> a[i];
    }
    for(int i =0; i < m; i++){
        cin >> b[i];
    }

    vector<vector<int>> d(n + 1,vector<int>(m + 1));
    vector<vector<char>> p(n + 1,vector<char>(m + 1));


    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if( i == 0 || j == 0){
                d[i][j] = 0;
                continue;
            }
            if(a[i - 1]==b[j - 1]){
                d[i][j] = d[i-1][j-1]+1;
                p[i][j] = 'd';
            }
            else{
                if(d[i-1][j] > d[i][j-1]){
                    d[i][j] = d[i-1][j];
                    p[i][j] = 'u';
                }else{
                    d[i][j] = d[i][j-1];
                    p[i][j] = 'l';
                }
            }
        }
    }

    vector<int> rst;
    while(n>0 && m > 0){
       if(p[n][m] ==  'd') {
          rst.push_back(a[n - 1]);
          n--;m--;
       }else if (p[n][m] ==  'u'){
           n--;
       }else m--;
    }
    while(!rst.empty()){
        cout << rst.back() << " ";
        rst.pop_back();
    }



    return 0;
}
