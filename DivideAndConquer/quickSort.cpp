#include <iostream>
#include <vector>
using namespace std;

// j -> to keep track of the boundary of the stuff we haven't looked at so far

// make it randomized
int choosePivot(vector<int> &A, int l, int r)
{
    // choose a random pivot
    int pivot = l + rand() % (r - l + 1);
    swap(A[l], A[pivot]);
    return A[l];
}

int partition(vector<int> &A, int l, int r)
{
    // essentially inpuy is A[l...r] r included
    int pivot = choosePivot(A, l, r);
    // pivot is the first element, make randomized later
    int i = l + 1; // i+1 is the left most element that is greater than the pivot
    for (int j = l + 1; j <= r; j++)
    {
        if (A[j] < pivot)
        {
            swap(A[i], A[j]);
            i++;
        }
    }
    swap(A[l], A[i - 1]); // swap pivot element with the right most element that is less than the pivot
    return i - 1;         // return the index of the pivot element
}

void quickSort(vector<int> &A, int l, int r)
{
    if (l < r)
    {
        int pivot = partition(A, l, r);
        quickSort(A, l, pivot - 1);
        quickSort(A, pivot + 1, r);
    }
}

int main()
{
    vector<int> v = {3, 8, 2, 5, 1, 4, 7, 6};
    quickSort(v, 0, v.size() - 1);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
}