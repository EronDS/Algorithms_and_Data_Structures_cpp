# Graph

## Graph Traversal

### Breadth-First Search (BFS)

Traversal prioritizing breadth. Starting from a given node, explore all neighbors at the current depth before moving to nodes at the next depth level.

**Algorithmic steps:**

1. Add start node to queue and mark as visited.
2. While queue is not empty:
   - Dequeue front element and print it.
   - For each unvisited neighbor of current node:
     - Add neighbor to queue and mark as visited.

### Depth-First Search (DFS)

Traversal prioritizing depth. Starting from a given node, explore as far as possible along each branch before backtracking.

**Algorithmic steps:**

1. Add start node to stack and mark as visited.
2. While stack is not empty:
   - Pop top element from stack and print it.
   - For each unvisited neighbor of current node:
     - Add neighbor to stack and mark as visited.

## Shortest Path Algorithms

### Dijkstra's Algorithm (MinimumPath)

Find the shortest path between two specific nodes in a weighted graph with non-negative edge weights.

**Implementation approach:**

Uses a greedy approach with distance relaxation, selecting the unvisited node with minimum distance at each step.

**Key formula:** $d[v] = \min(d[v], d[u] + weight(u,v))$

Where:
- $d[v]$ = shortest distance to node $v$
- $d[u]$ = shortest distance to node $u$
- $weight(u,v)$ = weight of edge from $u$ to $v$

**Algorithmic steps:**

1. Initialize distance array: Set distance to start node as 0, all others as infinity.
2. Create path map to track parent nodes for path reconstruction.
3. Mark start node as current and add to visited list.
4. While not reached target node:
   - For each neighbor of current node:
     - Calculate new distance: `current_distance + edge_weight`
     - If new distance is shorter than existing distance, update distance and parent.
   - Select unvisited node with minimum distance as next current node.
   - Add current node to visited list.
5. Reconstruct shortest path by backtracking through parent nodes.
6. Output total distance and complete path.
