#include <iostream>
#include <vector>
#include <sstream>

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0;    // initial index of first subarray
    int j = 0;    // initial index of second subarray
    int k = left; // initial index of merged array

    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        k++;
        i++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main()
{
    std::vector<int> arr;
    std::cout << "Enter array elements separated by space\n";

    // int num;
    //  while (std::cin >> num)
    //  {
    //      arr.push_back(num);
    //  } exits if letters are entered but not \na
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    int num;
    while (iss >> num)
    {
        arr.push_back(num);
    }

    std::cout << "You entered the following array: ";
    for (int el : arr)
    {
        std::cout << el << " ";
    }

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "\nSorted array: ";
    for (int el : arr)
    {
        std::cout << el << " ";
    }

    return 0;
}
