class Solution(object):
    def toNum(self, time):
        return int(time[0:2]) * 60 + int(time[3:5])
        
    def findMinDifference(self, timePoints):
        """
        :type timePoints: List[str]
        :rtype: int
        """
        if len(timePoints) > 1440:
            return 0
        times = {}
        for time in timePoints:
            time = self.toNum(time)
            val = times.get(time, 0)
            if val > 0:
                return 0
            times[time] = val + 1
        timePoints = sorted(times.iterkeys())
        print timePoints
        n = len(timePoints)
        best = 1441
        for i in range(len(timePoints)):
            diff = ((timePoints[i] - timePoints[(i-1 + n)%n]) + 1440) % 1440
            best = min(diff, best)
        return best