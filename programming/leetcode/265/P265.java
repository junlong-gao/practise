package com.junlonga.app.P265;

/**
 * Created by jungao on 7/25/16.
 */
public class P265 {
    public int minCostII(int[][] costs) {
        int K = costs[0].length;
        int[][] table = new int[K][2];
        int[] last = new int[2];
        int[] lastIndex = new int[2];
        lastIndex[0] = lastIndex[1] = -1;

        for(int i = 0; i < costs.length; i++){
            for(int k = 0; k < K; k++ ){
                for(int j = 0; j < 2; j++){
                    table[k][j] = last[j] + costs[i][k];
                }
            }
            int curMin = Integer.MAX_VALUE;
            int curMinIndex = -1;
            for(int k = 0; k < K; k++ ){
               for(int j = 0; j < 2; j++){
                   if(table[k][j] < curMin && k != lastIndex[j]){
                       curMin = table[k][j];
                       curMinIndex = k;
                   }
               }
            }
            int curSecMin = Integer.MAX_VALUE;
            int curSecMinIndex = -1;
            for(int k = 0; k < K; k++){
                for(int j = 0; j < 2; j++){
                    if(table[k][j] < curSecMin && k!= lastIndex[j] && k!= curMinIndex){
                        curSecMin = table[k][j];
                        curSecMinIndex = k;
                    }
                }
            }
            lastIndex[0] = curMinIndex; last[0] = curMin;
            lastIndex[1] = curSecMinIndex; last[1] = curSecMin;
        }
        return last[0];
    }
}
