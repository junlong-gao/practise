#include <iostream>
#include <cstdio>
using namespace std;

int main() {
   int count;
   scanf("%d", &count);
   while(count-->0) {
      int D, I;
      scanf("%d%d", &D, &I);
      I--;
      int node = 1;
      for (int i = 0; i < D - 1; ++i) {
         if (I % 2) {
            node = node * 2 + 1;
         } else {
            node = node * 2;
         }
         I >>= 1;
      }
      printf("%d\n", node);
   }
}

/*
 * Consider the 0th ball (has index 1), it will go left, and leave next 1th go
 * right, and then 2th left... so the first digit in the binary representation
 * of the index shows which subtree it will end up with.
 * Now for all the balls in the left subtree, the second digit oddness shows
 * which subtree it will go again.
 * When going for left, node = parent * 2, when right, node = parent * 2 + 1.
 * (recall heap)
 */
