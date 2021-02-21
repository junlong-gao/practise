class Solution {
    using ll = long long;
    ll count(ll prefix, ll n) {
        ll lo = prefix; ll hi = prefix;
        ll ret = 0;
        while (lo <= n) {
            ret += min(hi - lo + 1, n - lo + 1);
            lo = lo * 10;
            hi = hi * 10 + 9;
        }
        return ret;
    }

    ll search(ll rank, ll prefix, ll n) {
        if (rank == 1) {
            return prefix;
        }

        ll skipped = 1; // prefix itself
        for (ll d = 0; d <= 9; ++d) {
            if (prefix == 0 && d == 0) {
                continue;
            }

            ll next = prefix * 10 + d;
            ll tmp = count(next, n);
            if (skipped + tmp >= rank) {
                return search(rank - skipped, next, n);
            } else {
                skipped += tmp;
            }
        }

        assert(0);
    }
public:
    int findKthNumber(int n, int k) {
        return search(k + 1, 0, n);
    }
};