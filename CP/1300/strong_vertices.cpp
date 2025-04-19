#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// input: n, a[n], b[n]
// edge from u to v exists if au - av >= bu - bv
// so au - bu >= av - bv there there exists a vertex
// so to find the graph we can simply make c = au - bu
// then sort it in descending order
// if cu >= cv u-> there exists an edge
// so there will be an edge from everynode to all the nodes to its left. and also all the nodes with the same difference
// strong vertices can only be those with highest difference

void solve()
{

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &x : a)
        cin >> x;
    for (auto &x : b)
        cin >> x;

    vector<int> c(n);
    for (int i = 0; i < n; i++)
        c[i] = a[i] - b[i];
    int max_diff = *max_element(c.begin(), c.end());

    vector<int> strongVertices;
    for (int i = 0; i < n; i++)
    {
        if (c[i] == max_diff)
            strongVertices.push_back(i + 1);
        // one based indexing in graph
    }
    cout << strongVertices.size() << "\n";
    for (auto e : strongVertices)
    {
        cout << e << " ";
    }
    cout << "\n";
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