#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// revise!!

// 1500
// binary search, brute force, greedy
// mex: minimal excluded
// array a of length n, number k
// split a into k non overlapping subarrays b1,..,bk
// Mex(v) - smallest non negative integer that is not present in array v, so if zero is not present it will be zero and so on.
// maximise x = minimum MEX(bi)
// output x, the minimum MEX(bi)'s maximum possible value
// if you partition such taht 0 is present in every subarray then it will not be the minimum mex, then one and so on

// so you need at least k zeroes for it to not be x, then at least k ones, then k twos and so on.

// so for x to be the minimum mex(bi), 0 to x-1 must appear at least once in each of the subarrays.

// approach:

// binary search needs a monotonic predicate, a function or condition that changes in only one direction as you search variable increases
// want to find x such that MEX >= x
// if we can split array into k intervals, each having mex>=x
// then it means for x-1 also it holds
// and if we cannot split such that for each subarray 0 to x-1 exist, we definitely cannot do for x+1
// so check(x) -> check(x-1)
// ~check(x) -> ~check(x+1)

int subarrays(const vector<int> &a, int m)
{
    int count = 0, cur_mex = 0;
    // in the current sub array check if numbers from 0 to m are present or not
    vector<bool> present(m + 2, false);
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] <= m)
            present[a[i]] = true;
        // in the current subarray if the current mex is present then keep incrementing it as the mex would be such that 0,...mex-1 is present in the subarray
        while (present[cur_mex])
            cur_mex++;

        // want to check if m can be mex, if the cur_mex is greater then for m it is possible
        if (cur_mex >= m)
        {
            count++; // formed the subarray
            present.assign(m + 2, false);
            cur_mex = 0;
        }
    }
    return count;
}

void solve()
{

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &e : a)
        cin >> e;

    // binary search on x, the minimum mex(bi)

    int l = 0, r = n + 1, res = 0;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        // try to form subarrays
        // if you can form k such subarrays its good
        if (subarrays(a, m) >= k)
        {
            res = m;
            l = m + 1;
        }
        else
        {
            r = m - 1;
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