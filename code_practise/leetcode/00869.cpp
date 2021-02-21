class Solution {
public:
    bool reorderedPowerOf2(int N) {
        static const vector<unordered_map<int, int>> table = [&]() {
            vector<unordered_map<int, int>> ret;
            for (int i = 0; i < 32; ++i) {
                int v = 1 << i;
                unordered_map<int, int> rep;
                while (v) {
                    rep[v%10]++;
                    v /= 10;
                }
                ret.push_back(rep);
            }
            return ret;
        }();
        
        unordered_map<int, int> rep;
        while(N) {
            rep[N%10]++;
            N /= 10;
        }
        for (const auto & e : table) {
            if (e == rep) return true;
        }
        return false;
    }
};