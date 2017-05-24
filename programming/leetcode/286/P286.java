package com.junlonga.app.P286;

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;
import java.util.Queue;

/**
 * Created by jungao on 7/24/16.
 */
public class P286 {
    final int[] dx = {-1, 0 , 1, 0};
    final int[] dy = {0, -1, 0, 1};
    boolean valid(int[][] rooms, Boolean[][] visited, int x, int y){
        if(x >= rooms.length || x < 0) return false;
        if(y >= rooms[0].length || y < 0) return false;
        if(visited[x][y]) return false;
        if(rooms[x][y] == -1 || rooms[x][y] == 0) return false;
        return true;
    }
    public void wallsAndGates(int[][] rooms) {
        if(rooms.length == 0) return;
        final int room = 2147483647;
        class pair{
            int x, y;
            public pair(int x, int y){ this.x = x; this.y = y; }
        }
        Boolean visited[][] = new Boolean[rooms.length][rooms[0].length];
        for(Boolean[] row: visited){
            Arrays.fill(row, false);
        }
        Deque<pair> q = new ArrayDeque<pair>();
        for(int i = 0; i < rooms.length; i++){
            for(int j = 0; j < rooms[0].length; j++){
                if(rooms[i][j] == 0){ q.add(new pair(i, j)); }
            }
        }
        while(!q.isEmpty()){
            pair top = q.poll();
            for(int k = 0; k < 4; ++k){
                pair next = new pair(top.x + dx[k], top.y + dy[k]);
                if(valid(rooms, visited, next.x, next.y)){
                    visited[next.x][next.y] = true;
                    rooms[next.x][next.y] = Math.min(rooms[top.x][top.y] + 1, rooms[next.x][next.y]);
                    q.add(next);
                }
            }
        }
    }
}
