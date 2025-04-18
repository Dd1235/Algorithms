#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// used a greedy strategy

// need to notify n people
// cost p each pthread_setconcurrency
// for ith resident has got the announcement at least once,, he or she can share to at most ai residents ta bost bi for each share
// minimum total cost

// residents, share based on least cost per person
// then based on how many people you can share with desc

long long solve(int n, int p, vector<pair<int, int>> &a)
{

    // algorithm: keep a left pointer, which will keep track of the guy that will next share the news, so this is till a[l].first < p
    // keep track of till where we have reached that is once you educate a guy, keep extending to the right educating low cost guys using this left one,
    // stop when it is not useful to make use of a[l].first
    // then simply announce to the rest with p

    int remaining = n - 1;
    long long cost = p; // share with the first guy
    for (int i = 0; i < n and remaining > 0; ++i)
    {
        int c = a[i].first;
        int people = a[i].second;

        int shares = min(people, remaining);
        if (c < p)
        {
            cost += 1LL * c * shares;
            remaining -= shares; // each guy shares wtih at least one person so if you are currently somewhere then this person has been shared teh news by the previous people
        }
        else
        {
            break;
        }
    }
    cost += 1LL * remaining * p;
    return cost;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, p;
        cin >> n >> p;
        vector<pair<int, int>> a(n);
        for (auto &e : a)
        {
            cin >> e.second; // number of people
        }
        for (auto &e : a)
        {
            cin >> e.first; // cost
        }
        sort(a.begin(), a.end(), [](auto &x, auto &y)
             {
            if (x.first != y.first) return x.first < y.first;
            return x.second > y.second; });

        cout << solve(n, p, a) << "\n";
    }
}