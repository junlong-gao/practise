maintain a deque
the key observation is that the new comming element num[i]
will discard all element in the deque that less than num[i] from the back,
keep popping them until hit one not less than num
then the new back is the max of [i - k + 1, i]