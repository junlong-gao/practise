#include "../debug.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;
using l_int = long long;
l_int my_abs(l_int t){
    return t > 0? t: -t; 
}
int main() {
    l_int N; cin >> N;
    vector<l_int> a;
    for(int i = 0; i < N; ++i){
        l_int t; cin >> t;
        a.push_back(t);
    }
    sort(a.begin(), a.end());
    l_int cur_max = numeric_limits<l_int>::min();
    l_int index;
    l_int P,Q; cin >> P; cin >> Q;
    //first pass:
    l_int pmin = numeric_limits<l_int>::max();
    l_int qmin = numeric_limits<l_int>::max();
    for(int i = 0; i < N; ++i){
        l_int diffp, diffq;
        diffp= abs(P-a[i]);
        diffq= abs(Q-a[i]);
        pmin = min(pmin,diffp);
        qmin = min(qmin,diffq);
    }
    DEOUT("pmin",pmin);
    DEOUT("qmin",qmin);
    cur_max = max(pmin,cur_max);
    cur_max = max(qmin,cur_max);
    if(pmin>=qmin) index = P;
    else index = Q;
    DEOUT("index",index);
    //second pass:
    for(l_int i = 0; i+1 < N; ++i){
       l_int diff = a[i+1] - a[i];
       if(diff > 0){
           l_int mid = (a[i]+a[i+1])/2;
           l_int t_max = abs(mid - a[i]);
           if(mid >= P && mid <= Q){
               if(t_max > cur_max){
                   cur_max = t_max;
                   index = mid;
                   DEOUT("t_max", t_max);
                   DEOUT("mid", mid);
               }
           }
           if(mid*2!=diff){
               mid++;
               if(mid >= P && mid <= Q){
                   if(t_max > cur_max){
                       cur_max = t_max;
                       index = mid;
                       DEOUT("t_max", t_max);
                       DEOUT("mid", mid);
                   }
               }
           }
       }
    }
    cout << index <<endl;

    return 0;
}
