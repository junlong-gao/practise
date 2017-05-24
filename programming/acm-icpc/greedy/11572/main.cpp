#include <unordered_set>
#include <iostream>
#include <cstdlib>
#include <vector>

namespace Solution{
    using namespace std;
    vector<int> A;
    int n;
    void readInput(){
        cin >> n;
        for(int i = 0; i < n; ++i){
            int t; cin >> t;
            A.push_back(t);
        }
    }
    void run(){
        int T; cin >> T;
        while(T--){
            readInput();
            int L, R;
            L = R = 0;
            int ans = 0;
            unordered_set<int> s;
            while(R < n){
                while(R < n && !s.count(A[R])) s.insert(A[R++]);
                ans = max(ans, R-L);
                while(L < R && s.count(A[L])) s.erase(A[L++]);
            }
            cout << ans << "\n";
        }
    }
}

int main(){
    Solution::run();
    return 0;
}
