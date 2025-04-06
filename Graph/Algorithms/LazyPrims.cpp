#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge
{
    int u;
    int v;
    int w;
};
struct CompareEdge
{
    bool operator()(const Edge &a, const Edge &b)
    {
        return a.w > b.w;
        // "a is heavier → lower priority → goes down"
        // for min heap, if a.w > b.w, a is heavier, so it should have lower priority
        // if operator(a,b) returns true a has lower priority b has higher priority, b popped first
    }
};
int main()
{
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    int n = 5;
    vector<vector<pair<int, int>>> adj(n);
    vector<tuple<int, int, int>> edges = {
        {0, 1, 1}, {0, 2, 3}, {0, 3, 4}, {1, 2, 2}, {2, 3, 4}, {3, 4, 5}, {2, 4, 6}};

    for (auto &[u, v, w] : edges)
    {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // for (int u = 0; u < n; ++u)
    // {
    //     cout << "Node " << u << ": ";
    //     for (auto &[v, w] : adj[u])
    //     {
    //         cout << "(" << v << ", " << w << ") ";
    //     }
    //     cout << endl;
    // }

    // can unpack this like for (auto [u, v, w] : edges)
    // start with node 0
    vector<bool> visited(n, false);
    visited[0] = true;
    for (auto &[v, w] : adj[0])
    {
        pq.push({0, v, w});
    }
    while (!pq.empty())
    {
        auto [u, v, w] = pq.top();
        pq.pop();
        if (visited[v])
            continue;
        visited[v] = true;
        cout << "Edge: " << u << " - " << v << " with weight: " << w << endl;
        for (auto &[next, next_w] : adj[v])
        {
            if (!visited[next])
            {
                pq.push({v, next, next_w});
            }
        }
    }
}