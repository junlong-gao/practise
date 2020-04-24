class Solution {
    /*
    find kth element (k is rank, not index in the sorted array)
    nums1 [s1, l) [l, e1)
    nums2 [s2, r) [r, e2)

    wlg, let e1 - s1 <= e2 - s2, e1 - s1 >= 1, pick l, r such that (l + r) <= k (k > 1)
    if (nums1[l - 1] > nums2[r - 1]) {
        // why? can any element in nums2[s2...r] be the kth element?
       return search(nums1, s1, e1, nums2, s2 + r, e2, k - r);
    } else {
       return search(nums1, s1 + l, e1, nums2, s2, e2, k - l);
    }
    */
    int search(const vector<int>& n1, int s1, int e1,
               const vector<int> &n2, int s2, int e2,
               int k) {
        if (e1 - s1 > e2 - s2) {
            return search(n2, s2, e2, n1, s1, e1, k);
        }
        if (e1 - s1 == 0) {
            return n2[s2 + k - 1];
        }
        if (k == 1) {
            return min(n1[s1], n2[s2]);
        }
        int l = min(e1 - s1, k / 2); // since e1 - s1 >= 1, l >= 1
        int r = min(e2 - s2, k / 2); // r >= l >= 1
        // so the below recursion must terminate
        if (n1[s1 + l - 1] > n2[s2 + r - 1]) {
            return search(n1, s1, e1, n2, s2 + r, e2, k - r);
        } else {
            return search(n1, s1 + l, e1, n2, s2, e2, k - l);
        }
    }
public:
    // 1 2 3 4 5
    // 1 2 3 4
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int l = (nums1.size() + nums2.size() + 1) / 2;
        int r = (nums1.size() + nums2.size() + 2) / 2;
        return ((double)search(nums1, 0, nums1.size(), nums2, 0, nums2.size(), l) +
               (double)search(nums1, 0, nums1.size(), nums2, 0, nums2.size(), r)) / 2.0;
    }
};