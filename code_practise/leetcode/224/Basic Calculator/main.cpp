//
//  main.cpp
//  Basic Calculator
//
//  Created by John on 9/19/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Solution {
public:
    int calculate(string s) {
        int num = 0, result = 0, sign = 1;
        vector<int> stack;
        for(int i = 0; i < s.length(); i ++){
            if(s[i]>='0'&&s[i]<='9'){
                num = num * 10 + s[i] - '0';
            }else if (s[i] == '+'){
                result = result + sign*num;
                sign  = 1; num = 0;
            }else if (s[i] == '-'){
                result = result + sign* num;
                sign = -1; num = 0;
            }else if(s[i] == '('){
                stack.push_back(result);
                stack.push_back(sign);
                result = 0; sign = 1; num = 0;
            }else if(s[i] == ')'){
                result = result + sign*num;
                sign = stack.back(); stack.pop_back();
                result = stack.back() + result*sign; stack.pop_back();
                num = 0; sign = 1;
            }
        }
        return result + sign * num;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Solution mysolutions;
    cout << mysolutions.calculate("1-(5)");
    return 0;
}
