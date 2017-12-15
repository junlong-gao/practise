#include "../debug.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


using l_int = long long;
int check(char c){
    if(c - 'a' >=0 && c-'a' <26) return c-'a';
    if(c - 'A' >=0 && c - 'A' < 26) return c-'A';
    return -1;
}
int main() {
    string buf;
    getline(cin,buf);
    vector<int> alphabet(26,0);
    for(auto &c: buf){
        int index = check(c);
        if(index >=0)
            alphabet[index]++;
        DEOUT("index",index);
    }
    bool is =true;
    for(int i = 0; i < 26; ++i){
        if(alphabet[i] == 0) {
            is = false;
            break;
        }
    }
    if(is) cout << "pangram" << endl;
    else cout << "not pangram" << endl;
    
    return 0;
}

