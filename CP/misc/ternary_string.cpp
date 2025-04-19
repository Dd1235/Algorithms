#include <iostream>
#include <string>
#include <vector>
#include <climits>
// 1200
// sliding window

using namespace std;

// the solution will look something like abbbbbc
// the second it is like abbbbbbba you shift pointers to get ba

// two pointers kinda, what is the smallest length of a string that ends at index i

int solve(const string &s)
{
    int n = s.size();
    vector<int> freq(3);
    int l = 0;
    int min_len = INT_MAX;

    for (int r = 0; r < n; ++r)
    {
        freq[s[r] - '1']++;

        // shrink the window while it still contains all 3 characters
        while (l < r and freq[0] > 0 && freq[1] > 0 && freq[2] > 0)
        {
            min_len = min(min_len, r - l + 1);
            freq[s[l] - '1']--;
            l++;
        }
    }

    return (min_len == INT_MAX) ? 0 : min_len;
}

int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s; // consists of only 1 2 or 3
        cout << solve(s) << "\n";
    }
}