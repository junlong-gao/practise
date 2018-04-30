#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <deque>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"

namespace Solution{
    using namespace std;
    void run(){

    }
}

int main(){
    std::ifstream in(FILENAME);
    if(DEBUG){
        std::cin.rdbuf(in.rdbuf());
    }
    Solution::run();
    return 0;
}
