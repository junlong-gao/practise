/*
let c(n) be the number of valid seq of length n consisting only P and L with
no more 2 consecutive L's.
For any w in c(n), if w end in P, then w[n-1] must be an element of c(n - 1),
and vice versa.
However, if w end in L, then w[n-1] must also be an element of c(n-1), but the
converse is not true: for some element in c(n-1), if we append L to it, is
not in c(n). We need to subtract these elements from c(n-1). To wit, we note that
these sequences must be the ones in c(n - 1) and also end in LL. These sequences
are valid in c(n - 1), so the next char before LL must be P. Finally, the rest
n - 4 are all in c(n - 4) and vice versa, as any valid sequences can append P
to get another valid sequence. Therefore, we subtract c(n -4) from c(n - 1).
so c(n) = c(n - 1) + c(n - 1) - c(n - 4).

To consider valid sequence of length n with char A, we consider:
if it does not have A, then it is c(n);
else, if A is at index i (i = 1, 2, ... n) the part before A and the part after
A must be c(i) and c(n - 1 - i), respectively, 
*/
class Solution {
   using ll = long long;
   const ll m = 1e9+7;
public:
    int checkRecord(int n) {
        vector<ll> c = {1, 2, 4, 7};
        for (int i = 4; i <= n; ++i) {
            c.emplace_back(((2 * c[i - 1] % m) + m - c[i - 4]) % m);
        }
        ll ret = c[n];
        for (int i = 0; i < n; ++i) {
            ret = (ret + (c[i] * c[n - 1 - i] % m)) % m;
        }
        return ret;
    }
};
