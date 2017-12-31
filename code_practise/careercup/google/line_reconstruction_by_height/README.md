#Problem Domain
Suppose you have a line of n people in which the k-th person is described by a pair (h,t) , where h is the height of the k-th person and t is the number of people in front of k who have a height greater or equal than h . Write an algorithm to reconstruct the line.

For example, if the line is composed by the following people:
```
[(7, 0),(4, 4),(7,1), (5, 0), (6,1), (5, 2)]
```
The original line should be:
```
[(5,0), (7,0), (5,2), (6,1), (4,4),(7,1)]
```

#Approach:
Sort by height from high to low. if
```(x, t)``` requires t people 
higher ```x``` before this 
person, just insert it to position
```t```. Keep doing this from
the highest.
