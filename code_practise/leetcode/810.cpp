/*
 * > lcg 810
 *   Accepted
 *   168/168 cases passed (22 ms)
 */
/*
 * [828] Chalkboard XOR Game
 *
 * https://leetcode.com/problems/chalkboard-xor-game/description/
 *
 * algorithms
 * Hard (33.82%)
 * Total Accepted:    673
 * Total Submissions: 2K
 * Testcase Example:  '[1,1,2]'
 *
 * We are given non-negative integers nums[i] which are written on a
 * chalkboard.  Alice and Bob take turns erasing exactly one number from the
 * chalkboard, with Alice starting first.  If erasing a number causes the
 * bitwise XOR of all the elements of the chalkboard to become 0, then that
 * player loses.  (Also, we'll say the bitwise XOR of one element is that
 * element itself, and the bitwise XOR of no elements is 0.)
 * 
 * Also, if any player starts their turn with the bitwise XOR of all the
 * elements of the chalkboard equal to 0, then that player wins.
 * 
 * Return True if and only if Alice wins the game, assuming both players play
 * optimally.
 * 
 * 
 * Example:
 * Input: nums = [1, 1, 2]
 * Output: false
 * Explanation: 
 * Alice has two choices: erase 1 or erase 2. 
 * If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the
 * elements of the chalkboard is 1 XOR 2 = 3. Now Bob can remove any element he
 * wants, because Alice will be the one to erase the last element and she will
 * lose. 
 * If Alice erases 2 first, now nums becomes [1, 1]. The bitwise XOR of all the
 * elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.
 * 
 * 
 * 
 * Notes: 
 * 
 * 
 * 1 <= N <= 1000. 
 * 0 <= nums[i] <= 2^16.
 * 
 * 
 * 
 * Digestion:
 * Consider x in nums. If x appear for even times, it does not contribute to
 * final XOR. So only the value appearing for odd time matters.
 *
 * Let c(S) = # of elements appearing for odd times in state S.
 *
 * Let c(S) is even and fixed, 
 *    then if c(S) == 0, we are done (winning)
 *    else, we remove any value x in c (appearing for odd time), because its
 *    count > 0 (appear for odd times). This makes c(S \ {x}) = c(S) - 1 and c
 *    become odd.
 *
 * Let c(S) is odd and fixed,
 *    If one removes a value appearing for even time (not 0), its count will become odd,
 *    making c(s \ {x}) = c(s) + 1 even.
 *    If one removes a value appearing for odd time, its count will become even and
 *    making c(s \ {x}) = c(s) - 1 even.
 *
 * This strategy allow us to conclude inductively as long as c is even, we
 * can find a way to turn c into odd, and no matter what our opponent does, it
 * will become even again.
 *
 * Because if state is odd, the player cannot win, and there must be one winner
 * since the game finishes in finite steps, the one maintaining even state must
 * win through the above strategy.
 * 
 * Therefore, if c is even in the beginning, Alice can win, otherwise its opponent
 * can use the strategy and Alice must lose.
 *
 * As a special case, if originally nums has xor = 0, Alice automatically wins.
 */
class Solution {
public:
    bool xorGame(vector<int>& nums) {
       int ret = 0;
       unordered_map<int, int> count;
       for (auto n : nums) {
          count[n]++;
          ret = ret ^ n;
       }

       if (ret == 0) return true;

       int counter = 0;
       for (auto pr : count) {
          if (pr.second % 2 == 1) {
             counter++;
          }
       }
        
       return counter%2 == 0;
    }
};


/*
TESTS
[1, 2]
[1, 1, 2]
[1, 1]
[1]
[1, 2, 3, 4, 5, 5]
[1, 2, 3, 4]
[1, 1, 1, 1]
[1, 2, 3, 3]
[1, 2, 3]
[1, 1, 1]
*/
