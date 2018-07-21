// you can use includes, for example:
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
const int module = 1e6;
using ll = unsigned long long;
/*
[1, 1]
[1, 0]
to nth is
[F_{n+1}, F_{n}]
[F_{n}, F_{n-1}]
*/

vector<vector<ll>> mMult(const vector<vector<ll>> &l, const vector<vector<ll>> &r) {
    vector<vector<ll>> ret(2, vector<ll>(2, 0));

    for (int i = 0; i < 2; ++i) { for (int j = 0; j < 2; ++i) {
        for (int k = 0; k < 2; ++k) {
           cout  << l[i][k] <<  " " << r[k][j] << endl;
            ret[i][j] = (ret[i][j] + (l[i][k] * r[k][j]) % module) % module;
        }
    }}

    return ret;
}
vector<vector<ll>> mPower(int n) {
   cout << n << endl;
    const static vector<vector<ll>> &m {{1, 1}, {1, 0}};

    if (n == 1) {
        return m;
    }
    if (n == 0) {
        return {{1, 0}, {0, 1}};
    }

    vector<vector<ll>> ret(2, vector<ll>(2, 0));
    vector<vector<ll>> mSqrt = mPower(n/2);

    ret = mMult(mSqrt, mSqrt);

    if (n % 2) {
        ret = mMult(ret, m);
    }

    return ret;
}

int solution(int N) {
    auto ret = mPower(N);
    return ret[0][1];
}

int main() {
   //cout << solution(1) << endl;
   cout << solution(8) << endl;
   return 0;
}
