#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool check(string& w){
  int minj = -1;
  int i_j;
  for(int i = (int)w.length() - 1; i >=0; --i){
    for(int j = i - 1; j >=0; --j){
        if(w[j] < w[i] && j > minj ){
            minj = j;
            i_j = i;
            continue;
        }
    }
  }
  if (minj == -1) return true;
  swap(w[minj], w[i_j]);
  //cout << minj << endl;
  sort(w.begin() + minj + 1, w.end()); 
  return false;
}

int main() {
    int n = 0;
    cin >> n;
    while(n > 0){
        n--;
        string w;
        cin >> w;
        //cout << w <<endl;
        if(check(w)) cout << "no answer\n";
        else cout << w << "\n";
    }
    return 0;
}
