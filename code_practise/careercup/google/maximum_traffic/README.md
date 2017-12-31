##Problem Definition:
You are given a graph with no cycles, each node representing different cities and there are stadiums for baseball games in all cities.

Each node contains a value representing the population of the city, and a list of neighbors. (feel free to extend data structure)

Every time there is a baseball game at a city, everyone from all the different cities will go to the city with the baseball game.

Return the maximum traffic between a city and its neighbors when there is a game at that city, for all cities in O(n) time. (Does not have to be sorted)

Examples:
```
Input:
1   2
 \ /
  5
 / \
4   3
Output:
1 14
2 13
3 12
4 11
5 4

Input:
      7
     /
1   2
 \ / \
  5   15
 / \
4   3
Output:
1 36
2 15
3 34
4 33
5 24
7 30
15 22
```
##Approach:
My observation is that , for every node we essentially inspect it twice: first when we discover it via its parent (entering), second is leaving after when we return back from all its neighbor except for its visited parent that lead us to discover the node (since the graph is acyclic).
Here is the pesudo code omitting input and preprocessing:
```
def enter(v):
    flow = 0
    for u in adj(v) not visited[u]:
      visited[u] = True
      rst = enter(u)
      flow += rst 
      v.min = min(v.min, rst)
    v.min = min(v.min, total_population_count - v.population - flow)
    return v.population + flow


visited[0] = True
enter(0)
for v in nodes:
      print v.min
```
thus each enter function call just need to return the flow from v to the node that discovers v, on the fly calculate the min flow from all its neighbors.