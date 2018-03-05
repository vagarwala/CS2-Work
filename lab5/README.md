Caltech CS2 Assignment 5: Graphs

See [assignment5.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/graphs/blob/master/assignment5.html)


1. DFS Debugging: (1)
This algorithm has a problem - it could loop forever on an undirected graph, or one with cycles. To fix this problem, you could keep track of nodes that have already been visitedby giving the nodes a boolean attribute "visited" and setting that to true once they have been explored.  Then we would not visit them again when running through the algorithm so that every node is visited at most once.

2. Discussing MSTs: (1)

What is a MST?:
The three most essential properties of a MST (minimum spanning tree) are essentially the three things alluded to by its name - 1) it must be a tree, or an acyclic subset of the edges E(G), 2) it must span, i.e. it must visit every vertex of the graph, and 3) the sum of its edge weights must be minimal.

First step:
We should pick the adjacent node with the lowest edge weight, or cost, connecting it to the node we have. This is because we want to minimize the weight of the all the edges, and this first step obviously does so.

Next steps: 
At each subsequent step, we should pick the new node that can be reached from the nodes we have already visited, at the lowest cost.  It is essentially the same as the first step, except we are considering edges branching off of all the nodes we have seen so far.  We are finished when there are no more new nodes to add.

Different Algorithm:
We should pick the edge with the least weight at each step, as long as it does not create a cycle. We do this to minimize the weight of our final tree. It will essentially create multiple different unconnected trees and then slowly connect them.  We stop until there is only one tree left. We do this so that our tree spans all the nodes and we have always picked the lowest-cost edges possible.


3. Outline of Prim's Algorithm: (1)

1) Pick a first vertex.
2) Pick the edge with the minimum weight/cost that has one vertex in the tree and one vertex outside it.
3) Add that edge to the tree we are building.
4) Add the new vertex we've reached to the list of vertices we've seen.
5) Repeat steps 2-4 until all vertices are in the tree.

4. Outline of Dijkstra's Algorithm: (1)

1) for every point, nitialize distance to infinity (or like integer max value) (except source which is distance = 0), intialize previous = NULL, mark all vertices as unvisited (except the source).
2) Current vertex v = source
3) For each unvisited neighbor u of v:
    - calculate new_cost = v.cost + weight(Edge(v,u))
    - if new_cost < u.cost, we've found a cheaper path to u
    - set u.cost = new_cost
    - u.prev = v
4) Mark v as visited, because we have explored all possibilities going out of v.
5) set v = unvisited vertex with smallest cost (so far)
6) Go back to step 3 (until no more unvisited vertices, or unless
v is the destination)