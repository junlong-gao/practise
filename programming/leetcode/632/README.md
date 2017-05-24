[link](https://leetcode.com/problems/smallest-range/#/description)
Key observation:
* If [a, b] is a solution, then a and b are all in the list
* therefore, we can use a brute force approach by iterating the values, using a priority queue and let x = min(all current heads),  and check for all values y >= x, verifying range [x, y] satisfies the requirement.
* however, we can have a greedy approach. Given the current heads and for all values y >= x, we know we don't have to check values w < max(all current heads). Further, the values w > max(all current heads) are of no use as they cannot be optimal. In this way, the greedy choice can be used to reduce complexity without missing the optimal.
* To be precise, greedy's correctness lies in the fact that the choices greedy giving up does not affect finding the optimal. That is, the optimal must not be in the choices that greedy doesn't look.
