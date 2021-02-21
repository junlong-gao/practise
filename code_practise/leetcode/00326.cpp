static int x=[](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    bool isPowerOfThree(int n) {
        static const int magic = [](){
            long long t = 1;
            while (t * 3 <= numeric_limits<int>::max()) {
                t *= 3;
            }
            return t;
        }();
        return n > 0 && magic % n == 0;
    }
};
