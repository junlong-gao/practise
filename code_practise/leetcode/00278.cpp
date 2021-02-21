#include <vector>

using namespace std;
// Forward declaration of isBadVersion API.

bool isBadVersion(int version){
    return version >= 2;
}

class Solution {
public:
    int firstBadVersion(int n) {
        int l = 1, r = n, m;
        while(l < r){
            m = l + (r - l)/2;
            if(isBadVersion(m)){
                r = m;
            }else{
                l = m + 1;
            }
        }
        return l;
    }
};
