#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

class DSU
{
    vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (x != parent[x])
            parent[x] = find(parent[x]); // path compression
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x == root_y)
            return false; // already in the same set (would form a cycle)

        // union by rank
        if (rank[root_x] < rank[root_y])
            parent[root_x] = root_y;
        else if (rank[root_x] > rank[root_y])
            parent[root_y] = root_x;
        else
        {
            parent[root_y] = root_x;
            rank[root_x]++;
        }
        return true;
    }
};

int main()
{
    int n = 5;
    vector<Edge> edges = {
        {0, 1, 1}, {0, 2, 3}, {0, 3, 4}, {1, 2, 2}, {2, 3, 4}, {3, 4, 5}, {2, 4, 6}};

    sort(edges.begin(), edges.end());
    DSU dsu(n);

    vector<Edge> mst;
    int totalWeight = 0;

    for (Edge &e : edges)
    {
        if (dsu.unite(e.u, e.v))
        {
            mst.push_back(e);
            totalWeight += e.w;
        }
    }

    cout << "Minimum Spanning Tree edges:\n";
    for (Edge &e : mst)
    {
        cout << e.u << " -- " << e.v << " == " << e.w << "\n";
    }
    cout << "Total weight of MST: " << totalWeight << "\n";

    return 0;
}
