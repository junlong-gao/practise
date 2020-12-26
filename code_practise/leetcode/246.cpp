#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

class Solution {
public:
    bool isStrobogrammatic(string num) {
    	string rst;
        for(auto c:num){
        	string t = maper(c);
        	if(t=="") return false;
        	else rst.append(t);
        }
        reverse(rst.begin(),rst.end());
        //cout<<rst<<"\n";
    	if(rst == num){
    		 return true;
    	}else{
    		return false;
    	}
    }

    string maper(char c){
    	stringstream ss;
    	string s; 
    	ss << c;
    	ss >> s;
    	if(c=='0'||c=='1'||c=='6'||c=='8'||c=='9'){
    		if(c=='6'){
    			return "9";
    		}
    		if(c=='9'){
    			return "6";
    		}else{
    			return s;
    		}
    	} else {
    		return "";
    	}
    }
};

int main(){
	Solution mysolution;
	string a = "969";
	if(mysolution.isStrobogrammatic(a)){
		cout << "yes\n";
	}else{
		cout<<"no\n";
	}
	return 0;
}