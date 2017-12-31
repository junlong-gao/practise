//
//  main.cpp
//  Ugly Number II
//
//  Created by John on 9/13/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> ugly;
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 2;
        }
        ugly.push_back(1);
        int k;
        int t1 = 0, t2 = 0, t3 = 0;
        for (int i = 1; i < n; i++) {
            int k = min(2*ugly[t1],min(3*ugly[t2], 5*ugly[t3]));
            ugly.push_back(k);
            if (k == 2*ugly[t1]) {
                t1++;
            }
            if (k == 3*ugly[t2]) {
                t2++;
            }
            if (k == 5*ugly[t3]) {
                t3++;
            }
        }
        return ugly.back();
    }
};
int main(int argc, const char * argv[]) {
    Solution mysolution;
    cout<<mysolution.nthUglyNumber(2);
    return 0;
}
