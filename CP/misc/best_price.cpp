#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// revise! understand

// 1600

// n customers
// want to buy christmas tree
// price <= ai, buy the tree leave a good review
// price <= bi buy leave with negative review
// otherwise not buy at all

// calculate maximum earnings, given no more than k negative reviews
// upto k negative reviews allowed

// for a fixed price p, p <=bi they buy, if p > ai they leave negative review

// brute force
// for each possible price, check buyers and negative reviews, if less enough update max revenue
// tle

// if I check for a price, and it has a lot of negative reviews, then increasing the price might decrease negative reviews because some people won't buy it, it might also increase the revenue since price is higher and some people might be willing to buy it

// if it works for a price, less negative reviews, and then no need to check prices lesser than it, now if you decrease the price, someonee might buy it and give negative reivew

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (auto &x : a)
        cin >> x;
    for (auto &x : b)
        cin >> x;

    vector<pair<int, int>> prices;
    for (int i = 0; i < n; i++)
    {
        prices.emplace_back(a[i], 0); // will give positive review
        prices.emplace_back(b[i], 1); // will buy at this price and give negative review
    }
    sort(prices.begin(), prices.end());
    long long res = 0;
    int buyers = n, neg = 0;
    for (int i = 0; i < 2 * n;)
    {
        auto [p, r] = prices[i]; // current price
        if (neg <= k)
            res = max(res, p * 1LL * buyers);
        while (i < 2 * n and prices[i].first == p)
        {
            if (prices[i].second == 0)
                neg++;
            if (prices[i].second == 1)
            {
                neg--;
                buyers--;
            }
            ++i;
        }
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