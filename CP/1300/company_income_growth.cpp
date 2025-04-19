#include <iostream>
#include <vector>

using namespace std;

// greedy

// a[i] income of the  company in 2000 + ith year (one based indexing from 2001 onwards)
// choose y1,..yk such that y1 1 , y2 2 etc.
// longest increasing subsequence? but such that it increases by one exactly

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;

    vector<int> res;
    int income = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == income + 1)
        {
            res.push_back(i);
            income++;
        }
    }
    cout << res.size() << "\n";
    for (auto e : res)
    {
        cout << 2001 + e << " ";
    }
}

int main()
{
    solve();
}