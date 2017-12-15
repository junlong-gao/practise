//
//  main.cpp
//  Longest Valid Parentheses
//
//  Created by John on 9/27/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
	int longestValidParentheses(string s) {
		stack<int> stk;
		stk.push(-1);
		int maxL=0;
		for(int i=0;i<s.size();i++)
		{
			int t=stk.top();
			if(t!=-1&&s[i]==')'&&s[t]=='(')
			{
				stk.pop();
				maxL=max(maxL,i-stk.top());
			}
			else
				stk.push(i);
		}
		return maxL;
	}
};
int main(int argc, const char * argv[]) {
	// insert code here...
	
	Solution mysolution;
	string test = ")()()())";
	
	mysolution.longestValidParentheses(test);
	std::cout << "Hello, World!\n";
    return 0;
}
