#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include <algorithm>


namespace queens{
    using namespace std;
    bool col[8], main_diag[15], sub_diag[15];
    bool placed[8][8];
    int so_far = 0;
    const int queens = 8;
    void dfs(int placed_row){
        if(placed_row == queens){
            cout << so_far++ << endl;
            for(int i = 0; i < queens; ++i){
                for(int j = 0; j < queens; j++){
                    if(placed[i][j]) cout << "x ";
                    else cout << "o ";
                }
                cout << "\n";
            }
        }else{
            for(int i = 0; i < queens; ++i){
                if(!col[i] && !main_diag[placed_row + i] && !sub_diag[queens - i + placed_row]){
                    col[i] = main_diag[placed_row + i] = sub_diag[queens-i+placed_row] = true;
                    placed[placed_row][i] = true;
                    dfs(placed_row + 1);
                    placed[placed_row][i] = false;
                    col[i] = main_diag[placed_row + i] = sub_diag[queens-i+placed_row] = false;
                }
            }
        }
    }
}
int main(){
    using namespace queens;
    fill(col, col+8,false);
    fill(main_diag, main_diag+15,false);
    fill(sub_diag, sub_diag+15,false);
    dfs(0);


    return 0;
}
