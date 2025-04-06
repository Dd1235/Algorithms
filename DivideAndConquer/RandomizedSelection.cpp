#include <iostream>
#include <vector>

int partition(std::vector<int> &arr, int l, int r)
{
    int p = arr[l];
    int i = l + 1;
    for (int j = l + 1; j <= r; j++)
    {
        if (arr[j] < p)
        {
            std::swap(arr[i++], arr[j]);
        }
    }
    std::swap(arr[l], arr[i - 1]);
    return i - 1; // index of the pivot
}

int RSelect(std::vector<int> &arr, int left, int right, int i)
{
    if (right <= left)
        return arr[left];
    int j = partition(arr, left, right); // pivot index

    if (j == i - 1)
        return arr[j];
    else if (j > i - 1)
        return RSelect(arr, left, j - 1, i);
    else
        return RSelect(arr, j + 1, right, i); // don't use i - j because that might be the orders statistic when you just consider the right part of the array but also its being used to compared with the index of the pivot and the index of the pivot is with respect to the entire array and not just the part you consider
}
int main()
{
    std::vector<int> nums = {15, 18, 12, 9, 6, 3, 21, 27, 24};
    int orderStatistic = 4;

    int result = RSelect(nums, 0, nums.size() - 1, orderStatistic);
    std::cout << "The " << orderStatistic << "th order statistic using Randomized Selection is : " << result << std::endl;

    return 0;
}