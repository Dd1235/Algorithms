#include <iostream>
#include <vector>
#include <limits>
#include <tuple>

using namespace std;

const int INF = 1e9;

int main()
{
    int n = 5;
    int m = 7;
    int source = 0;

    vector<tuple<int, int, int>> edges = {
        {0, 1, 1},
        {0, 2, 3},
        {0, 3, 4},
        {1, 2, 2},
        {2, 3, 4},
        {3, 4, 5},
        {2, 4, 6}};

    vector<int> dist(n, INF);
    dist[source] = 0;
    // Relax edges up to n-1 times
    for (int i = 0; i < n - 1; i++)
    {
        for (auto &[u, v, w] : edges)
        {
            if (dist[u] != INF and dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }
    }
    // if can relax again, then there is a negative cycle
    bool hasNegativeCycle = false;
    for (auto &[u, v, w] : edges)
    {
        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            hasNegativeCycle = true;
            break;
        }
    }
    if (hasNegativeCycle)
    {
        cout << "Graph contains a negative weight cycle\n";
    }
    else
    {
        cout << "Shortest distances from source node " << source << ":\n";
        for (int i = 0; i < n; ++i)
        {
            if (dist[i] == INF)
            {
                cout << "Node " << i << ": INF\n";
            }
            else
            {
                cout << "Node " << i << ": " << dist[i] << "\n";
            }
        }
    }

    return 0;
}