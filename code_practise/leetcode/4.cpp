class Solution {
#define V vector
    // find kth element, 1th is the smallest. For the kth element, at least
    // k elements <= it.
    // On average we reduce size by k/2, T(k) = T(k/2) + O(1), k = O(m + n), T(m+n)=O(log(m+n))
    
    // key idea: divide and conquer by discarding a region:
    // the region's element cannot be the solution because the rank we search > the rank they can
    // have
    // 1. pick the first part of each array, make sure they are small enough to reason about their ranks.
    //    => their total size is <= k
    // 2. the "smaller" one will then have rank <= k - 1, hence all of them will have rank at most k - 1
    // 3. they are the region to be discarded.
    // 4. make sure each time we discard a non-empty region so it will always terminate
    //    => just let each region be the min of (k/2, original region length), and handle cases k/2 = 0 -> k = 1
    //       and original region length = 0 -> pick the other region.
    int findK(int k, V<int> &a, V<int> &b, int as, int ae, int bs, int be) {
        if (as == ae) {
            return b[bs+k-1];
        } else if (bs == be) {
            return a[as+k-1];
        }
        if (k == 1) {
            return min(a[as], b[bs]);
        }
        
        int am = min(k/2, (ae - as));
        int bm = min(k/2, (be - bs));
        // l + m <= k;
        
        if (a[as + am - 1] >= b[bs + bm - 1]) {
           /*
           ... a[as + am - 1] a[as + am] ...
           ... b[bs + bm - 1] b[bs + bm] ...
           all elements b[bs ... bs + bm - 1] (m of them) cannot be of rank k
           because they are at most rank (am + bm) - 1 <= k - 1 < k
           */
           return findK(k - bm, a, b, as, ae, bs + bm, be);
        } else {
           return findK(k - am, a, b, as + am, ae, bs, be);
        }
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); int m = nums2.size();
        double m1 = findK((n+m)/2 + 1, nums1, nums2, 0, n, 0, m);
        if ((n+m)%2) {
            return m1;
        }
        double m2 = findK((n+m)/2, nums1, nums2, 0, n, 0, m);
        return (m1 + m2) / 2;
    }
};
