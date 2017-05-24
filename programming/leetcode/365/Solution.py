class Solution(object):
    def canMeasureWater(self, x, y, z):
        def gcd(x, y):
            while x:
                x, y = y % x, x
            return y

        return z == x + y or (z < x + y and z % gcd(x, y) == 0)

if __name__ == "__main__":
    s = Solution()
    assert s.canMeasureWater(5,3,4)
    assert not s.canMeasureWater(2,6,5)
    assert s.canMeasureWater(1,2,3)
