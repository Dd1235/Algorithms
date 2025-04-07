# Graphs

## Algorithms

- The graph can be visualized using [Algorithms/DrawGraph.hpp](Algorithms/DrawGraph.hpp)

It looks something like:
<img src="./graph1.png" alt="graph" width="300">

### Kahn's Algorithm for Topological Ordering

- Topological ordering is useful for Program build dependencies, event scheduling etc.
- We essentially remove nodes without dependencies, and their edges, and this continues till we encounter a cycle or all nodes are removed from graph
- BFS based
- Implementation [here](Algorithms/TopologicalSortKahns.cpp)

```cpp
vector<int> topologicalSort(vector<vector<int>> &graph, vector<int> &inDegree)
{
    // O(V+E) time complexity

    int n = graph.size();
    vector<int> sorted;
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        sorted.push_back(node);

        for (int neighbour : graph[node])
        {
            inDegree[neighbour]--;
            if (inDegree[neighbour] == 0)
            {
                q.push(neighbour);
            }
        }
    }
    if (sorted.size() != n)
        sorted.clear();
    return sorted;
}
```

### DFS for Topological Ordering

- Implementation [here](Algorithms/TopologicalSortDFS.cpp)
- We maintain a recursion stack to detect cycles

```cpp
bool dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &recStack, stack<int> &st)
{
    visited[node] = true;  // Mark the node as visited
    recStack[node] = true; // Add the node to the recursion stack

    // Explore all neighbors
    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            // If the neighbor is unvisited, recursively visit it
            if (dfs(neighbor, adj, visited, recStack, st))
            {
                return true; // Cycle detected in the subtree
            }
        }
        else if (recStack[neighbor])
        {
            // If the neighbor is already in the recursion stack, a cycle is detected
            return true;
        }
    }

    recStack[node] = false; // Remove the node from the recursion stack
    st.push(node);          // Add the node to the stack for topological sort
    return false;           // No cycle detected
}
vector<int> topologicalSort(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false); // Tracks the recursion stack
    stack<int> st;

    // Perform DFS for all unvisited nodes
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (dfs(i, graph, visited, recStack, st))
            {
                return {}; // Return an empty vector if a cycle is detected
            }
        }
    }

    // Extract nodes from the stack to get the topological order
    vector<int> sorted;
    while (!st.empty())
    {
        sorted.push_back(st.top());
        st.pop();
    }

    return sorted;
}
```

### Dijkstra
- 
- Implementation [here](Algorithms/DijkstraBinHeap.cpp)
SSSP
Input: 
- Directed graph G = (V,E)
- each edge has a non negative length
- source s
Output: 
- for each v , compute L(v) := legntho f shortest s-v path in 

Assumptions:
1. [for convinience] there exists s->v path
2. No negative edge lengths

Bellman ford for negative edge length

Why another shortest path algorithm? 

question: Doesnt BFS already compute shortest path in linear time? 
ans: yes but only when edge length are one. 

question: why not just replace each edge with unit length edges? 
ans: blows up graph too much

```psedocode
Initialize:
- X = {s} // vertices processed so far
- A[s] = 0 // computed shortest path distances
- B[s] = empty path // computed shortest path for bookkeeping
Main loop:
- while X ≠ V:  // need to grow X by one node
    - some edges cross from X to V-X and some that go from V-X to X
    - among all `(v,w) ∈ E`, with `v ∈ X, w ∉ X` pick the edge that minimizes the following criterion:
        A[v] + $ l_{vw} $ (Dijkstras greedy criterion)
    - add w* to X
    - set A[w*] = A[v*] + l_vw
```

Naive implementation: O(mn)

Use heap: O(mlogn)

Invariant #1:

elements in heap - vertices of V-X

Invariant #2:

for v not in X
key[v] = smallest Dijkstra greedy score of an edge (u,v) and u belongs ot X

Two round tournament

Maintaining the invaraint 2:

On adding w, the edges that are now crossing the frontier, that are from w to V-X need to be added

key[v] needs to be changed for neighbours of w that are not in X
- for each edge (w,v) in E:
    - if v belongs to V - X ie heap
    - deleve v from heap
    - recompute key[v] = min{key[v], A[w]+lwv}

- work done through heap Assumptions
- (n-1) Extract mins
- each edge (v,w) triggers at most one delete / insert combo (if v added to X before w), if w added first v wont experience any key changed
- so # of heap operations if O(n+m) = O(m)
- so O(mlogn)


### Prims Algorithms

- greedy MST algorithm that works well on dense graphs.
- Meets or imrpoves on the bounds of Kruskals/Boruvkas
- Cannot each find minimum spanning forest
- Lazy: O(ELogE) but eager verison is O(ELogV)

Lazy version:

- main a PQ that sorts edges by min edge cost.
- Start at any node s. Mark as visited ans add all edges to PQ
- while PQ is not empty:
    - deque edge e from PQ
    - if e connects two visited nodes, discard it, it is outdated
    - else add it to MST and mark the new node as visited and add all edges to PQ
    - when number of edges is n-1 we know we have a MST


Eager Version(to be implemented):

- track (node, edge) key values pairs
- for any MST with directed edges, each node is paired with exactly one of its incoming edges. Except the start node
- undirected graph -> make an equivalent directed graph 
- determine which incoming edges to include in MST
- so retreive (node, edge) pairs
- use Indexed Priority Queue (PQ)
- sorted key value pairs
- O(ElogV)

- works for negative edges

### Cut Property


- smallest edge crossing any cut is part of MST
- proof: 
    - suppose edge e that is cheapest edge crossing cut (A,B) yet e is not in MST
    - exchange e another edge to make it cheaper
    - some or the other edge would be crossing (A,B) from MST
    - this is subtle, we do not know if this exchange leads to a spanning tree
    - removing f might make disconnected, adding e might make cycle
    - hope: how to identify this beautiful edge that can be exchanged?
    - e = (u,v), but there already exists a path from u to v in the MST
    - so adding e creates a cycle
    - call it C, cycle created by adding e to T*
    - The edge to be swapped is on this cycle.
    - how to be sure there exists e'?
    - double crossing lemma: if there is a cycle that crosses the cycle at least once, it has to cross at leats twice.
    - T = T* u {e}  - {e'} is also a spanning tree

![](cut.png)

### Kruskals Algorithm

- The globally minimum weight edge is going to be the minimum edge for every it crosses
- Tricky part: do not add edges that create cycle, that the two vertices are already connected
- Union find (Disjoint set) data structure
- Union finds were invented to make Kruskals faster
- Fibonacci heaps were invented to make Dijkstra faster


- T = empty
- all v in V: makeset(v)
- sort E by weight - O(mlogm)
- for e = {u,v} in E:
    - if find(u) != find(v):
        - union(u,v)
        - T = T u {e}

- Uion find time complexity: 
    - can solve v in alpha(n), inverse ackerman function, very slow growing function

O(sort(e)) + e(alpha(v)) + v
- if your weights are integers
- then we can use radix sort, linear time sorting
- so for smaller weights: Kruskals is better

- To generate a random spanning tree, just pick an edge, check if you can add it, and add it

![](kruskal.png)

### Bellman Ford
- SSSP
- can have negative weight cycles

ex: Given undirected graph G, does G have a negative weight cycle? Not particularly interesting, if there is negative weighted edge, that itself is a negative weight cycle.

only useful to talk about the directed case

ex: alg A solves SSSP in O(V(V+E)), show how to solve in O(VE)
- they would only differ if V>>E. But given its single source, connected component with s can have at most E+1 vertices. So just through away vertices  not reachable from s.
- if graph not simple, just consider min weight edge between any two vertices

Claim 1: if delta(s,v) is finite, there exists a shortest s v path that is simple.
- proof: if there exists a cycle, since finite weight, cycle cannot have negative weight, so just remove the cycle.

Number of edge in a simple shortest path is at most V-1
- find shortest paht distances by limiting the number of edges you can go through
- k-Edge distances
- $ \delta_k(s,v) $ = weight shortest path from s to v with at most k edges

Claim 2: if $ \delta_|v|(s, v) < \delta_{|v|-1}(s,v) $ first path cannot be simple, contains a negative weight cycle, then delta(s,v) = -inf, so if there is a vertex v like this, it is a witness

- Proof: suffices: every negative weight cycle contains a witness.
![](bf1.png)

Bellman-Ford idea: Graph Duplication

Make |V|+1 levels, v_k in level k represents reaching vertex v using at most k edges.

If we connect edges from one level to only higher levels, then this graph is DAG. (linear time)
- O(V(V+E))


The recurrence:

\[
d[i][v] = \min\left(d[i-1][v], \min_{(u \to v)} d[i-1][u] + w(u,v)\right)
\]

Can be simplified in **practical implementation** to just:

\[
\text{if } dist[u] + w < dist[v] \text{ then update } dist[v] = dist[u] + w
\]

