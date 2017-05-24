class Solution(object):
    def leastBricks(self, wall):
        """
        :type wall: List[List[int]]
        :rtype: int
        """
        v = {}
        best = 0
        length = 0
        for row in wall:
            x = 0
            for b in row[:-1]:
                x = x + b
                count = v.get(x, 0)
                v[x] = count + 1
                best = max(best, v[x])
        return len(wall) - best 