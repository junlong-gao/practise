#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include <algorithm>

namespace nine{
    using namespace std;
    void anagSort(vector<string>& li){
        sort(li.begin(), li.end(), 
                [&](const string& lhs, const string& rhs){
                    string cpl(lhs), cpr(rhs);
                    sort(cpl.begin(), cpl.end());
                    sort(cpr.begin(), cpr.end());
                    return cpl < cpr;
                });
    }
    int rotatedBinarySearch(vector<int>& li, int x){
        int l = 0, r = li.size() - 1;
        while(l < r){
            int m = l + (r - l + 1) /2;
            if(li[m] == x) return m;
            if(li[l] == x) return l;
            if(li[r] == x) return r;
            if(li[l] <= li[m]){
                if(x>=li[l] && x < li[m]){
                    r = m + 1;
                }else{
                    l = m;
                }
            }else{
                if(x <= li[r] && x > li[m]){
                    l = m + 1;
                }else{
                    r = m;
                }
            }
        }
        return li[l] == x ? l : -1 ;
    }
    int LIS(vector<pair<int, int>>& a){
        sort(a.begin(), a.end(), [&]
                (const pair<int,int>& lhs, const pair<int,int>& rhs){
                    if(lhs.first < rhs.first) return true;
                    else if(lhs.first == rhs.first) return lhs.second < rhs.second;
                    return false;
                });
        vector<pair<int,int>> tails;
        tails.push_back(a[0]);
        for(int i = 1; i < (int)a.size(); ++i){
            auto it = lower_bound(tails.begin(), tails.end(),a[i],
                    [&](const pair<int,int>& lhs, const pair<int,int>& rhs){
                        return lhs.second < rhs.second;
                    });
            if(it==tails.end()){
                tails.push_back(a[i]);
                //cerr << a[i].second << endl;
            }
            else{
                    *it = a[i];
            }         
        }
        return tails.size();
    }
}
int main(){
    using namespace nine;
    vector<string> li = {"aaw", "aab","app",  "baa", "aba","waa"};
    nine::anagSort(li);
    for(auto& ele: li){
        cout << ele << endl;
    }
    vector<int> numbers = {1,2,0};
    cout << rotatedBinarySearch(numbers, 2) << endl;
    vector<pair<int,int>> a;
    a.emplace_back(60,100);
    a.emplace_back(70,150);
    a.emplace_back(56,90);
    a.emplace_back(75,190);
    a.emplace_back(60,95);
    a.emplace_back(68,110);
    cout << LIS(a) <<endl;

    return 0;
}
