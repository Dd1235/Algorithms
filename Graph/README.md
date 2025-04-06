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