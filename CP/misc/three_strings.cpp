#include <iostream>
#include <string>
#include <vector>
#include <climits>
// 1500
// dp

using namespace std;

int solve(string &a, string &b, string &c)
{
    int n = a.length();
    int m = b.length();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++)
        dp[i][0] = dp[i - 1][0] + (a[i - 1] != c[i - 1]); // only take letters from a

    for (int j = 1; j <= m; j++) // only letters from b
        dp[0][j] = dp[0][j - 1] + (b[j - 1] != c[j - 1]);

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            int c_idx = i + j - 1;
            // if you know how to build the first i+j letters of c taking i letters from a and j letters from b
            // you know how to buld i+j+1 letters of c either using i+1, j or i,j+1
            int pick_a = dp[i - 1][j] + (a[i - 1] != c[c_idx]);
            int pick_b = dp[i][j - 1] + (b[j - 1] != c[c_idx]);

            dp[i][j] = min(pick_a, pick_b);
        }
    }

    return dp[n][m];
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string a;
        cin >> a;
        string b;
        cin >> b;
        string c;
        cin >> c;

        cout << solve(a, b, c) << "\n";
    }
}