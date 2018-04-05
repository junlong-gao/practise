/*
 * [118] Pascal's Triangle
 *
 * https://leetcode.com/problems/pascals-triangle/description/
 *
 * algorithms
 * Easy (40.00%)
 * Total Accepted:    167.6K
 * Total Submissions: 419.1K
 * Testcase Example:  '0'
 *
 * Given numRows, generate the first numRows of Pascal's triangle.
 * 
 * 
 * For example, given numRows = 5,
 * Return
 * 
 * [
 * ⁠    [1],
 * ⁠   [1,1],
 * ⁠  [1,2,1],
 * ⁠ [1,3,3,1],
 * ⁠[1,4,6,4,1]
 * ]
 * 
 * 
 */
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
       if (numRows == 0) return {};

       vector<vector<int>> ret{{1}};
       for (int i = 1; i < numRows; ++i) {
          vector<int> rst;
          rst.push_back(1);
          for (int j = 1; j < i; ++j) {
             rst.push_back(ret.back()[j-1] + ret.back()[j]);
          }
          rst.push_back(1);
          ret.emplace_back(std::move(rst));
       }

       return ret;
    }
};


/*
TESTS
0
1
2
3
4
5
*/
