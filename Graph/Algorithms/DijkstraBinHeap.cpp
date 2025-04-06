#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    int n, m;
    cout << "Enter number of vertices and edges space separated: ";
    cin >> n >> m;
    cout << "\n";
    int u, v, w;

    // adjacency list
    vector<pair<int, int>> adj[n];
    // adj[u] contains all pairs {v,w} , so adj is an array of std::vector conatiners

    for (int i = 0; i < m; i++)
    {
        cout << "Enter source, dest, weight : ";
        cin >> u >> v >> w;
        cout << "\n";
        adj[u].push_back({v, w});
    }

    priority_queue<pair<int, int>> pq;
    int distance[n];
    for (int i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
    }
    int source;
    cout << "Source vertex : ";
    cin >> source;
    distance[source] = 0;
    pq.push({0, source});
    vector<bool> visited(n, false);

    while (!pq.empty())
    {
        int curr = pq.top().second;
        // this is the vertex that is "nearest" so add it
        pq.pop();
        if (visited[curr])
            continue;
        visited[curr] = true;

        // for each pair {v,w} in adj[curr]
        for (auto p : adj[curr])
        {
            int nei, w;
            tie(nei, w) = p;
            if (distance[nei] > distance[curr] + w)
            {
                distance[nei] = distance[curr] + w;
                pq.push({-distance[nei], nei});
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << i << " " << distance[i] << "\n";
    }
}