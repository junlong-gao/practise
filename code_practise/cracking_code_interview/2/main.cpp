#include <iostream>
#include <vector>
#include <string>

using namespace std;

void replaceSpace(string& s, int length){
    int space = 0;
    for(int i = 0; i < length; ++i){
        if(s[i] == ' '){
            space ++;
        }
    }
    int newSize = length + 2 * space;
    s.resize(newSize);
    int j = newSize - 1;
    int i = length - 1;
    while(i >= 0 && j >=0){
        if(s[i] == ' '){
            s[j--] = '0';
            s[j--] = '2';
            s[j--] = '%';
        }else{
            s[j--] = s[i];
        }
        i--;
    }
}

void rotateLeftMatrix(vector<vector<int>>&  mat){
    int n = (int)mat.size();
    if(n == 1) return;

    for(int offset = 0; offset < n - offset; ++offset){
        for(int j = offset + 1; j < n - offset - 1; ++j){
            swap(mat[offset][j], mat[j][n - 1 - offset]);
            swap(mat[j][offset], mat[n - 1 - offset][j]);
        }
        for(int j = offset + 1; j < n - offset - 1; ++j){
            swap(mat[j][offset], mat[n - 1 - j][n - 1 - offset]);
        }
        int temp = mat[offset][offset];
        mat[offset][offset] = mat[offset][n - 1-offset];
        mat[offset][n - 1 -offset] = mat[n - 1-offset][n - 1-offset];
        mat[n- 1 -offset][n - 1 - offset] = mat[n - 1-offset][offset];
        mat[n - 1 - offset][offset] = temp;
    }
}
int main(){
    string test = "  ";
    replaceSpace(test, test.length());
    cout << test << endl;
    vector<vector<int>> mat = {{1,2,3},{5,6,7},{9,10,11}};
    rotateLeftMatrix(mat);
    for(auto& row: mat){
        for(auto entry: row){
            cout << entry << " ";
        }
        cout << "\n";
    }

    return 0;

}
