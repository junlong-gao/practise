class Solution {
    using ll = long long;
    
    // count tree size of prefix whose value <= n
    ll count(ll prefix, ll n) {
        ll ret = 0;
        ll lo = prefix, hi = prefix;
        while (n >= lo) {
            ret += min(hi - lo + 1, n - lo + 1);
            lo = lo * 10;
            hi = hi * 10 + 9;
        }
        return ret;
    }
    
    ll search(ll prefix, ll n, ll k) {
        if (k == 1) {
            return prefix;
        }
        
        ll skipped = 1; // skip prefix
        for (ll lastDigit = 0; lastDigit <= 9; ++lastDigit) {
            if (prefix == 0 && lastDigit == 0) {
                // no such subtree;
                continue;
            }
            
            ll nextNode = prefix * 10 + lastDigit;
            ll subTreeSize = count(nextNode, n);
            if (k <= skipped + subTreeSize) { 
                // decend into the node in tree nextnode which has rank: 
                // [skipped + 1, skipped + subtreesize]
                return search(nextNode, n, k - skipped);
            } else {
                skipped += subTreeSize;
            }
        }
        
        assert(0);
    }
public:
    int findKthNumber(int n, int k) {
        return search(0, n, k + 1); // the virtual root has rank 1, so shift by 1
    }
};