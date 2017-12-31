Duality: The stack trace for printing inorder of a bst is exactly its preorder.

consider the tree:
        10
    5       15
1       8       18
      7   9
has preorder 10 5 1 8 7 9 15 18

looks like (overlapping the first non decreasing):
1   7
5   8   9
10          15  18
is the tree rotated at 90 degrees

we can thus use this to print an ordered output from preorder,
and it is not valid iff the element examing now is less than the 
current ordered nodes' end.