// The problem of counting inversions in an array involves finding the number of pairs (i, j) such that i < j and array[i] > array[j]. An efficient algorithm for this problem is based on the divide and conquer paradigm, similar to the merge sort algorithm. The time complexity of this algorithm is O(n log n).

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// In C++, std::pair is a template class defined in the <utility> header that provides a way to store two heterogeneous objects as a single entity. It is a simple and useful tool for combining two values.

//  vector.begin() and vector.end() are iterators that reprsent the beginning and the end of a vector. vector.begin() - Runs an iterator pointing to the frist element of the vector. iterators are similar to pointers in that they allow you to access elements in a container.

pair<vector<int>, long long> merge_and_count_split(const vector<int> &left, const vector<int> &right)
{

    vector<int> merged;
    long long split_inversions = 0;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            merged.push_back(left[i]);
            i++;
        }
        else
        {
            merged.push_back(right[j]);
            split_inversions += left.size() - i;
            j++;
        }
    }

    merged.insert(merged.end(), left.begin() + i, left.end());
    merged.insert(merged.end(), right.begin() + j, right.end());

    return {merged, split_inversions};
}

pair<vector<int>, long long> count_inversions(vector<int> &arr)
{
    if (arr.size() <= 1)
    {
        return {arr, 0};
    }

    int mid = arr.size() / 2;

    // the range constructor of the vector takes two iterators indicating hte range of elements to include in the new vector

    vector<int> left_half(arr.begin(), arr.begin() + mid);
    vector<int> right_half(arr.begin() + mid, arr.end());

    auto left_result = count_inversions(left_half);
    auto right_result = count_inversions(right_half);

    auto merged = merge_and_count_split(left_result.first, right_result.first);
    // gives you a pair, the merged array and the no of split_inversions

    long long total = left_result.second + right_result.second + merged.second;

    return {merged.first, total};
}

int main()
{
    vector<int> arr;
    string line;
    cout << "Enter the elements space separated: ";
    getline(cin, line);
    istringstream iss(line);
    int num;
    while (iss >> num)
    {
        arr.push_back(num);
    }

    auto result = count_inversions(arr);

    cout << "Sorted Array: ";
    for (int num : result.first)
    {
        cout << num << " ";
    }
    cout << "\nNumber of Inversions: " << result.second << endl;

    return 0;
}