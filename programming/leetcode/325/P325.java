package com.junlonga.app.problem325;

import java.util.HashMap;

/**
 * Created by jungao on 7/24/16.
 */
public class P325 {
    public int maxSubArrayLen(int[] nums, int k) {
        HashMap<Integer, Integer> sums = new HashMap<Integer, Integer>();
        int curSum = 0;
        int soFar = 0;
        for(int i = 0; i < nums.length; i ++){
            curSum += nums[i];
            if(curSum == k){
                soFar = Math.max(soFar, i+1);
            }else{
                Integer index = sums.get(curSum - k);
                if(index != null){
                    soFar = Math.max(soFar, i - index);
                }
            }
            if(!sums.containsKey(curSum)){
                sums.put(curSum, i);
            }
        }
        return soFar;
    }
}
