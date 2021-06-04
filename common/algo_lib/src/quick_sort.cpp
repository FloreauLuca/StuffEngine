#include "quick_sort.h"

namespace stuff::algo
{
std::vector<std::pair<size_t, size_t>> QuickSort::SortList()
{
    QuickSortFunc(0 ,list_.size() - 1);
    return swapList_;
}

int QuickSort::Partition(size_t low, size_t high)
{
    const int pivot = list_[high]; // pivot
    size_t i = low; // Index of smaller element and indicates the right position of pivot found so far

    for (size_t j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (list_[j] < pivot)
        {
            std::swap(list_[i], list_[j]);
            swapList_.push_back(std::pair<size_t, size_t>(i, j));
            coloredList_.push_back(std::vector<size_t>{i, j, high});
            i++; // increment index of smaller element
        }
    }
    std::swap(list_[i], list_[high]);
    swapList_.push_back(std::pair<size_t, size_t>(i, high));
    coloredList_.push_back(std::vector<size_t>{i, high});
    return (i);
}

void QuickSort::QuickSortFunc(size_t low, size_t high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        size_t pi = Partition(low, high);

        // Separately sort elements before
        // partition and after partition
    	if (pi > 0)
			QuickSortFunc(low, pi - 1);
        QuickSortFunc(pi + 1, high);
    }
}
}
