class Solution {
    void search(int i, vector<string> &sofar, string &col, string &l, string &r, vector<vector<string>> *output, int n) {
       if (i == n) {
          output->push_back(sofar);
           return;
       } 
        
        string nextRow(n, '.');
        
        for (int j = 0; j < n; ++j) {
            if (col[j] == '.' && l[n-1+i-j] == '.' && r[i + j] == '.') {
                nextRow[j] = col[j] = l[n-1 + i-j] = r[i + j] = 'Q';
                sofar.push_back(nextRow);
                search(i + 1, sofar, col, l, r, output, n);
                
                sofar.pop_back();
                nextRow[j] = col[j] = l[n-1+i-j] = r[i + j] = '.';
            }    
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
       string l(2*n - 1, '.'), r(2 * n - 1, '.'), col(n, '.');
        vector<string> sofar;
        vector<vector<string>> ret;
        search(0, sofar, col, l, r, &ret, n);
        return ret;
    }
};