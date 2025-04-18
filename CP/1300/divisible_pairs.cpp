#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

// x and y - favourite integers
// pair (i,j) is beautiful if x|(ai + aj) and y | (ai - aj)
// output number of beautiful pairs in the array
// if gcd(x,y) | 2ai then ai can form pairs, wont work out
// ai = -aj mod x
// ai = aj mod y

void solve()
{

    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n);
    for (auto &e : a)
    {
        cin >> e;
    }
    long long res = 0;
    map<pair<int, int>, int> count;

    for (int j = 0; j < n; j++)
    {
        int minus_mod_x = ((x - (a[j] % x)) + x) % x;
        int mod_y = a[j] % y;

        res += count[{minus_mod_x, mod_y}];
        count[{a[j] % x, mod_y}]++;
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