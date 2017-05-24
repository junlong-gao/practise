#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T = 0;
    cin >> T;
    vector<pair<int, int>> queries;
    int max_n = 1;
    while(T--){
        int s, e;
        cin >> s >> e;
        max_n = max(max_n, e);
        queries.emplace_back(s, e);
    }
    string s = "122";
    int i = 2;
    bool flip = true;
    while(s.length() <= max_n){
        char next = flip ? '1' : '2';
        flip = !flip;
        //cout << i << " " << s << endl;
        s += next;
        if(s[i] == '2') s += next;
        ++i;
    }
    vector<int> ones(max_n + 2), twos(max_n + 2);
    ones[0] = twos[0] = 0;
    for(int i = 1; i <= s.length(); ++i){
        ones[i] = ones[i-1] + (s[i-1] == '1' ? 1 : 0);
        twos[i] = twos[i-1] + (s[i-1] == '2' ? 1 : 0);
        //cout << ones[i] << " " << twos[i] << endl;
    }
    for(auto& pr: queries){
        if(pr.first == 1){
            cout << ones[pr.second] << endl;
        }else{
            cout << twos[pr.second] << endl;
        }
    }
    return 0;
}
