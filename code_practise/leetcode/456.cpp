/*
 * For every index i, we are interested in:
 * m[i]: the min value x[j] and j < i (to the left)
 * s[i]: the min value x[j] such that x[j] > m[i] and j > i(to the right and
 *       just barely larger thatn m[i])
 *
 * Then, we can tell if m[i] < x[i] < s[i], it has a 132 pattern.
 * if for all i, this relation cannot hold, then it cannot have a 132 pattern.
 *
 * Compute m[i] is trivial, compute s[i] is much more involved.
 *
 * Note that if nums[i] <= m[i], then nums[i] <= m[i - 1], so nums[i] cannot
 * be s[i - 1].
 *
 * The key observation is since m[i - 1] >= m[i]. If candidate x <= m[i], then
 * it cannot be a candidate for i - 1 either. Every element will only enter
 * candidate set once.
 *
 * Also note that if we find nums[i] > min(all nums[j] > m[j], j > i), then
 * we have found a solution, and nums[i] will not be a candidate for s[i - 1].
 * Therefore the candidate set is always in decreasing order when adding new
 * candidates.
 *
 * let s be the candidate set and assume we are about to compute s[i]. Since
 * candidate set s is ordered, we can remove from the smaller end (cf. above
 * paragraph) until we find s is empty or some s.back() > m[i]. In the latter
 * case s.back() is our s[i].
 *
 * If nums[i] is greater than m[i], we know nums[i] can be a candidate for s[i
 * - 1], otherwise nums[i] will not be inserted in the candidate set. Further
 *   verify that nums[i] > s[i], and if that is the case a solution is found.
 * Otherwise, if s is not empty we know the smallest candidate in s (s[i]) is
 * >= nums[i], and we will push it into the candidate set for i - 1. This
 * arrangement allows s to be a non-increasing sequence.
 */
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        if (nums.size() < 3) return false;
        vector<int> s, m{nums[0]};
        for (int i = 1; i < nums.size(); ++i) {
            m.push_back(min(m.back(), nums[i]));
        }
        for (int i = nums.size() - 1; i >= 0; --i) {
            while (!s.empty() && s.back() <= m[i]) {
                s.pop_back();
            }
            if (nums[i] > m[i]) {
                if (!s.empty() && s.back() < nums[i]) return true;
                s.push_back(nums[i]);
            }
        }
        return false;
    }
};
