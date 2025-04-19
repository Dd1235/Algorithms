#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

// revise

// non overlapping intervals! theres the hint that it is greedy, no need of dp

// find the maximum number of non overlapping beautiful segments in a
// a beautiful segment [l,r] has sum 0

// use a hashmap to remember the last index a sum has occured
// if overlapping better to pick the earlier occureing one
// since it will overlap with lesser intervals later
// if prefix[i] = prefix[j] it means that the sum from i+1 j is zero and that is one interval

// tle on test case 12, replacing unordered_map with map
// this worked
// look into unordered_map vs map

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &e : a)
        cin >> e;

    int lastIndex = -1; // ending index of previous interval
    long long prefix = 0;
    int res = 0;
    map<long long, int> lastOccurence;
    lastOccurence[0] = -1;
    for (int i = 0; i < n; i++)
    {
        prefix += a[i];
        if (lastOccurence.count(prefix))
        {
            int idx = lastOccurence[prefix] + 1; // index of the starting of the interval
            if (idx > lastIndex)
            {
                res++;
                lastIndex = i; // index of the ending of the last interval
            }
        }
        lastOccurence[prefix] = i;
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