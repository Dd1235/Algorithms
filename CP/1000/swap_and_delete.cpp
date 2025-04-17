#include <iostream>
#include <vector>
#include <string>

using namespace std;

// s is a binary string
// delete char -> 1 coin
// swap char -> free

// t, the operated string, is good if ti is not equal to s[i] for all i

// the approach of abs(oens-zeroes) does not work
// the idea is that imagine t is of length l
// we know what t is, it is simply inverse of s till point l
// then you have chosen to delete all the letters
// we have no new ways of "generating" ones or zeroes
// so till point l you have done swaps
// so while you can assign an opposite do it, when you cannot anymore you have to delete the letters

int solve(string &s)
{
    // returns the minimum cost to make t good
    int ones = 0, zeroes = 0;
    int n = s.size();
    for (auto c : s)
    {
        if (c == '0')
            zeroes++;
        else
            ones++;
    }
    for (int i = 0; i < n; i++)
    {
        int toPlace = s[i] == '0' ? 1 : 0;
        if (toPlace == 0)
        {
            if (!zeroes)
                break;
            zeroes--;
        }
        else
        {
            if (!ones)
                break;
            ones--;
        }
    }
    return ones + zeroes;
}

int main()
{
    int testcases;
    cin >> testcases;
    while (testcases--)
    {
        string s;
        cin >> s;
        cout << solve(s) << "\n";
    }
}