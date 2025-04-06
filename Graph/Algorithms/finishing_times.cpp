#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

class Graph
{
public:
    unordered_map<int, unordered_set<int>> adjList;
    unordered_map<int, int> finishingTimes;

    void addEdge(int src, int dest)
    {
        adjList[src].insert(dest);
    }

    void printAdjList()
    {
        cout << "Adjacency List:\n";
        for (const auto &pair : adjList)
        {
            int node = pair.first;
            cout << node << " -> ";
            for (int neighbor : pair.second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void DFSLoop(int n)
    {
        unordered_set<int> explored;
        int t = 0;

        for (int i = n; i > 0; i--)
        {
            if (explored.find(i) == explored.end())
            {
                DFS(i, explored, t);
            }
        }
    }
    void DFS(int i, unordered_set<int> &explored, int &t)
    {
        explored.insert(i);
        for (int neighbor : adjList[i])
        {
            if (explored.find(neighbor) == explored.end())
            {
                DFS(neighbor, explored, t);
            }
        }
        t++;
        finishingTimes[i] = t;
    }
};

int main()
{
    // Example usage
    int n = 9; // Number of nodes
    Graph g;

    g.addEdge(1, 7);
    g.addEdge(2, 5);
    g.addEdge(3, 9);
    g.addEdge(4, 1);
    g.addEdge(5, 8);
    g.addEdge(6, 3);
    g.addEdge(6, 8);
    g.addEdge(7, 4);
    g.addEdge(7, 9);
    g.addEdge(8, 2);
    g.addEdge(9, 6);

    g.DFSLoop(n);

    g.printAdjList();

    // Output finishing times and leaders
    cout << "Finishing times:\n";
    for (const auto &pair : g.finishingTimes)
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
