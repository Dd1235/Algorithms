#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 1600

// problem: rooted tree with n vertices, 1 is the root
// in the array a you have the parents (from root 2 to n)
// dx - distance from root to x
// at any vertex v you can move the chip to vertex u is du = dv + 1.
// u cannot be a neighbour of v(does not hold for root)
// calculate the number of valid sequences.

#define MOD 998244353

void solve()
{
    int n;
    cin >> n;
    vector<int> parent(n + 1);
    vector<vector<int>> adjList(n + 1, vector<int>());
    for (int i = 2; i <= n; i++)
    {
        cin >> parent[i];
        adjList[parent[i]].push_back(i);
    }
    vector<long long> pathsEnding(n + 1, 0);
    long long res = 1;
    pathsEnding[1] = 0;
    queue<int> q;
    for (int nei : adjList[1])
    {
        q.push(nei);
    }
    int prevLevelSum = 1;

    while (q.size())
    {
        long long currLevelSum = 0;
        int level = q.size();
        for (int i = 0; i < level; i++)
        {
            int node = q.front();
            q.pop();
            prevLevelSum %= MOD;
            // +mod is super important
            pathsEnding[node] = (prevLevelSum - pathsEnding[parent[node]] + MOD) % MOD;
            currLevelSum = (currLevelSum + pathsEnding[node]) % MOD;
            for (int nei : adjList[node])
                q.push(nei);
        }
        res = (res + currLevelSum) % MOD;
        prevLevelSum = currLevelSum % MOD;
    }

    cout << res << "\n";
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}