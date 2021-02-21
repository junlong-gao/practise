class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = nums1.size() - 1; int j = n - 1; int k = m - 1;
        while (j >= 0 && k >= 0) {
            if (nums1[k] > nums2[j]) {
                nums1[i] = nums1[k];
                i--; k--;
            } else {
                nums1[i] = nums2[j];
                i--; j--;
            }
        }
        
        while (k >= 0) {
            nums1[i] = nums1[k];
            i--; k--;
        }
        while (j >= 0) {
            nums1[i] = nums2[j];
            i--; j--;
        }
        return;
    }
};
