#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <cmath>
#include <unordered_set>
#include <algorithm>

using namespace std;


void updateBits(int& n, int& m, int i, int j){
    int mask = ~0;
    mask -= ((1 << j) - 1);
    mask |= ((1<<i) - 1);
    n = (n&mask)|(m<<i);
}

void bitToString(string& str, string& rst){
    auto decimal = str.find('.');
    stringstream ss(str.substr(0, decimal));
    int intPart = 0; ss >> intPart;

    double decPart = stod(str.substr(decimal, str.length() - decimal));
    rst.clear();
    while(intPart){
        char c = intPart % 2 + '0'; rst.push_back(c); intPart >>= 1;
    }
    for(int i = 0; i < (int)rst.length() - 1- i; ++i){
        swap(rst[i], rst[rst.length() - 1 -i]);
    }
    rst.push_back('.');
    unordered_set<double> residue;
    if(decPart > 1) decPart -= 1;
    while(1){
        residue.insert(decPart);
        decPart *= 2;
        if(residue.find(decPart) != residue.end()) break;
        else{
            residue.insert(decPart);
            if(decPart >= 1){
                rst.push_back('1');
                decPart -= 1;
            }else{
                rst.push_back('0');
            }
        }
    }
    if(rst.back() == '.') rst.pop_back();
}
void missingNum(vector<int> nums, int& so_far, int index){
    if(nums.empty()) return;
    vector<int> odd, even;
    for(int i = 0; i < (int)nums.size(); ++i){
        if(nums[i]%2){
            odd.push_back(nums[i] >> 1);
        }else{
            even.push_back(nums[i] >> 1);
        }
    }
    if(even.size() > odd.size()){
        so_far |= (1 << index);
        missingNum(odd, so_far, index + 1);
    }else{
        missingNum(even, so_far, index + 1);
    }
}
int main(){
    int n = 255; int i = 0; int j = 7;
    int m = 1;
    updateBits(n, m , i, j);
    //cout << n << endl;
    string str = "7.125", rst;
    bitToString(str, rst);
    cout << rst << endl;

    vector<int> nums = {0,1,3,4,5};
    int so_far = 0;
    missingNum(nums,so_far,0);
    cout << so_far << endl;


    return 0;
}
