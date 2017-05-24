//
// Created by Junlong Gao on 8/11/16.
//

#ifndef PRACTISE_SOLUTION_H_H
#define PRACTISE_SOLUTION_H_H
#include <string>
#include <vector>
#include "catch.hpp"
namespace{
using namespace std;
    class Solution_google_longest{
        int max = -1;
        void bfs(string &s, int i, int j, int level, int sofar){
            int k = i;
            while (k < j && s[k] != '\n'){ ++k;}
            for(int l = i; l < k; ++l){
                if(s[l] == '.'){ //this is a file
                    int cur = sofar + k - i;
                    if(cur > max){
                        max = cur;
                    }
                    return;
                }
            }
            sofar += k - i + 1;
            vector<int> dirs;
            while(k < j){
                while(k < j && s[k] != '\n') k++;
                int m = k + 1;
                while(m < j && s[m] == '\t') m++;
                int nextLevel = m - k - 1;
                if(nextLevel == level + 1){
                    //found a correct level:
                    dirs.push_back(m);
                }
                k = m;
            }
            int idx = 0;
            dirs.push_back(j + 2 + level);
            for(idx = 0; idx+1 < dirs.size(); ++idx){
                bfs(s, dirs[idx], dirs[idx+1] - 2 - level, level + 1, sofar);
            }
        }

    public:
        int ans(string& s){
            max = -1;
            bfs(s, 0, s.length(), 0, 0);
            return max;
        }
    };

    TEST_CASE( "test suite for longest absolute path in file system", "[1]" ) {
        Solution_google_longest testObj;
        string filesystem = "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext";
        REQUIRE( testObj.ans(filesystem)  == 20 );
        string f2 = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
        REQUIRE( testObj.ans(f2)  == 32 );
        string f3 = "dir\n\tsubdir1\n\t\tfileaaaaaaaaaaaaaaa1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
        REQUIRE( testObj.ans(f3)  == 36 );
    }
}

#endif //PRACTISE_SOLUTION_H_H
