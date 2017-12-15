package com.junlonga.app.problem_283_test;

/**
 * Created by junlonga on 7/24/2016.
 */
public class P283 {
    public void moveZeroes(int[] nums) {
        /*
        int j = 0;
        while(j < nums.length && nums[j] != 0) j++;
        while( j < nums.length){
            while( j < nums.length && nums[j] == 0){ j++;}
            if (j >= nums.length) break;
            for(int i = j; i - 1 >= 0 && nums[i-1] == 0 ; i--){
               int tmp = nums[i];
                nums[i] = nums[i-1];
                nums[i-1] = tmp;
            }
        }
        */
        int curPos = 0;
        for(int num:nums){
            if(num != 0) nums[curPos++] = num;
        }
        for(int i = curPos; i<nums.length; i++){
            nums[i] = 0;
        }
    }
}
