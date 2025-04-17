#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int solve(int n, vector<int> &a, int k)
{
    if (k == 2)
    {
        bool even = false;
        for (auto e : a)
        {
            if (e % 2 == 0)
            {
                even = true;
                break;
            }
        }
        if (even)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if (k == 3)
    {
        int least = INT_MAX;
        for (auto e : a)
        {
            if (e % 3 == 0)
                return 0;
            least = min(least, 3 - e % 3);
        }
        return least;
    }
    if (k == 5)
    {
        int least = INT_MAX;
        for (auto e : a)
        {
            if (e % 5 == 0)
                return 0;
            least = min(least, 5 - e % 5);
        }
        return least;
    }
    // k == 4
    int evens = 0;
    int least = INT_MAX;
    for (int num : a)
    {
        if (num % 4 == 0)
            return 0;
        else if (num % 2 == 0)
            evens++;

        least = min(least, 4 - num % 4);
    }
    if (evens >= 2)
        return 0; // 2 evens multiply to give 4
    else if (evens == 1)
        return 1; // just need to fix one more
    // n is at least 2 so fix the other odd number
    else                      // there are 2 or more odd numbers
        return min(2, least); // least could be one
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        // k can only be 2 or 3 or 4 or 5
        // if k==2 if there are only odd numbers in a then answer is 1
        // 3 and 5 are prime, if none of the a[i] are multiple, pick the one with least p-a[i]modp
        // for 4, you have have 2 even numbers of one multiple of 4 you are done
        // 1 even is there, pick one odd number to increase by one
        // all odd numbers two operations
        cout << solve(n, a, k) << "\n";
    }
}