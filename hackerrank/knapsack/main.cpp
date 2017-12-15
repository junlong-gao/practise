#include <iostream>
#include <vector>

using namespace std;
int max(const int a, const int b){
    return a > b ? a : b;
}
int main(){
    int T;
    cin >> T;
    while(T >0){
        T--;
        int n,k;
        cin >> n >> k;
        vector<int> a;
        vector<vector<int>> s(2, vector<int>(k+1));
        for(int i = 0; i < n; ++i){
            int t; cin >> t;
               a.push_back(t);
        }
        for(int j = 0; j <= k; ++j){
            if(j >= a[0])
                s[0][j] = j - j % a[0];
            else s[0][j] = 0;
        }
        for(int i = 1; i < n; ++i){
            s[i%2][0] = 0;
            for(int j = 1; j <= k; ++j){
                if(j >= a[i]) 
                    s[i%2][j] = max(s[i%2][j - a[i]] + a[i], s[(i-1)%2][j]);
                else s[i%2][j] = s[(i-1)%2][j];
            }
        }
        cout << s[(n-1)%2][k] << "\n";
    }
}
