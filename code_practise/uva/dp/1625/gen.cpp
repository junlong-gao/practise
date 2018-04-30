#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(){
    int n, m;
    cin  >> n >> m;
    cout << n << endl;
    srand(0xABABABAB);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << (char)('A' + rand()% 26);
        }
        cout << endl;
        for(int j = 0; j < m + 1; ++j){
            cout << (char)('A' + rand()% 26);
        }
        cout << endl;
    }

}
