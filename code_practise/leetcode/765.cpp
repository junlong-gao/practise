class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        vector<int> rev(row.size());
        for (int i = 0; i < row.size(); ++i) {
            rev[row[i]] = i;
        }
        
        int count = 0;
        for (int i = 0; i < row.size(); i = i + 2) {
            int t;
            if (row[i] % 2 == 0) {
                t = row[i] + 1;
            } else {
                t = row[i] - 1;
            }
            if (row[i + 1] == t) continue;
            
            count ++;
            int idx = rev[t];
            swap(row[i + 1], row[idx]);
            swap(rev[row[i + 1]], rev[row[idx]]);
        }
        
        return count;
    }
};

/*
Greedy.

Let (i, j) represent a swap of index at i and j. Assume i < j, then any optimal solution
must be a sequence of these swaps.

Two sequence of swaps are equivalent if they result in the same permutation.

Composition of swaps (i, j) * (l, k) means swap i and j, then l and k. If these 4 index are 
all distinct, then (i, j) * (l, k) = (l, k) * (i, j)


Fact 1:
let l < i < j
(i, j) * (l, k) = match k with 
| i -> (i, j) * (l, k) = (l, j) * (i, j)
| j -> (i, j) * (l, k) = (l, i) * (i, j)
| _ -> i, j) * (l, k) = (l, k) * (i, j)

Proof: verify by hand: when k = j
l  i  j          l  i  j
l  i  j          l  i  j
A  B  C          A  B  C
A  C  B (i, j)   B  A  C (l, i)
B  C  A (l, j)   B  C  A (i, j)

=> (i, j) * (l, j) = (l, i) * (i, j)

Fact 2:
For each optimal seq of swaps S, there exists an equivalent seq S' of swaps with the same number of
swaps such that for any two swaps (i, j) followed by (l, k), i < l.

Use fact 1 on S to move swaps with smaller index to the front of the seq.

Fact 3:
If you swap a pair of adjacent couple (their index are of the form (2k, 2k + 1)), the optimal swap seq remains the same,
with one adjustment of replacing the swapped couple.
... A B ...
has the same count of optimal swaps as
... B A ...
because if optimal matches A with A' by swapping out B in the first row, we can use that to construct an optimal of
the second row by replacing the index of B by decrementing it by 1.
If A B is already matched, optimal solution cannot touch A or B in both cases.

Fact 1, 2 says we can go from left to right (line 10)
Fact 3 says we can greedily choose to swap the index 2k + 1 only when we see it is necessary without losing the optimal
solution(line 17 ~ 22).
*/
