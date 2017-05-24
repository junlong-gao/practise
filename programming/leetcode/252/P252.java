package com.junlonga.app.problem252;

import java.util.Arrays;
import java.lang.*;

/**
 * Created by jungao on 7/24/16.
 */

class Interval {
    int start;
    int end;
    Interval() { start = 0; end = 0; }
    Interval(int s, int e) { start = s; end = e; }
}

public class P252 {
    public boolean canAttendMeetings(Interval[] intervals) {
        Arrays.sort(intervals, (Interval lhs, Interval rhs)-> lhs.start - rhs.start);
        for(int i = 0; i + 1 < intervals.length; i++){
            if(intervals[i].end > intervals[i+1].start) return false;
        }
        return true;
    }
}
