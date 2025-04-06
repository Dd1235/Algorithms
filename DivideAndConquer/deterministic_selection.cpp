#include <iostream>
#include <vector>

int partition(std::vector<int> &vec, int low, int high, int pivot)
{
    auto it = find(vec.begin(), vec.end(), pivot);
    std::swap(vec[it - vec.begin()], vec[high]);

    int i = low;
    for (int j = low; j < high; ++j)
    {
        if (vec[j] < pivot)
        {
            std::swap(vec[i], vec[j]);
            ++i;
        }
    }

    std::swap(vec[i], vec[high]);
    return i;
}

int dSelect(std::vector<int> &arr, int left, int right, int i)
{
    if (left == right)
        return arr[left];
    int n = right - left + 1;
    for (int i = 0; i < n / 5; i++)
    {
        std::sort(arr.begin() + left + i * 5, arr.begin() + left + i * 5 + 5);
    }
    int remaining = n % 5;
    if (remaining > 0)
    {
        std::sort(arr.begin() + left + (n / 5) * 5, arr.begin() + right + 1);
    }

    std::vector<int> medians;
    for (int i = 0; i < n / 5; i++)
    {
        medians.push_back(arr[left + i * 5 + 2]); // index 2 ie 3rd element of each sorted group
    }

    if (remaining > 0)
    {
        medians.push_back(arr[left + (n / 5) * 5 + remaining / 2]);
    }

    int p = dSelect(medians, 0, medians.size() - 1, medians.size() / 2);
    int pIndex = partition(arr, left, right, p);

    if (pIndex == i - 1)
        return arr[pIndex];
    else if (pIndex > i - 1)
        return dSelect(arr, left, pIndex - 1, i);
    else
        return dSelect(arr, pIndex + 1, right, i);
}

int main()
{
    std::vector<int> arr = {12, 3, 5, 7, 4, 19, 26, 15, 9, 30, 8, 10, 14, 18, 21, 1, 6, 22};
    for (int i = 1; i <= arr.size(); i++)
    {
        std::cout << "The " << i << " order statistic is " << dSelect(arr, 0, arr.size() - 1, i) << std::endl;
    }

    return 0;
}