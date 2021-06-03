#include "quick_sort.h"

namespace stuff::algo
{
std::vector<std::pair<size_t, size_t>> QuickSort::SortList()
{
    QuickSortFunc(0 ,list_.size() - 1);
    return swapList_;
}

size_t QuickSort::Partition(int low, int high)
{
    int pivot = list_[high]; // pivot
    size_t i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (size_t j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (list_[j] < pivot)
        {
            i++; // increment index of smaller element
            std::swap(list_[i], list_[j]);
            swapList_.push_back(std::pair<size_t, size_t>(i, j));
        }
    }
    std::swap(list_[i + 1], list_[high]);
    swapList_.push_back(std::pair<size_t, size_t>(i+1, high));
    return (i + 1);
}

void QuickSort::QuickSortFunc(int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        size_t pi = Partition(low, high);

        // Separately sort elements before
        // partition and after partition
        QuickSortFunc(low, pi - 1);
        QuickSortFunc(pi + 1, high);
    }
}
}
