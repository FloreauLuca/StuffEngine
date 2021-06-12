#include "algo/sort/quick_sort.h"

namespace stuff::algo
{
template<class T>
std::vector<std::pair<size_t, size_t>> QuickSort<T>::SortList()
{
    QuickSortFunc(0 ,this->list_.size() - 1);
    return this->swapList_;
}

template<class T>
int QuickSort<T>::Partition(size_t low, size_t high)
{
    const int pivot = this->list_[high]; // pivot
    size_t i = low; // Index of smaller element and indicates the right position of pivot found so far

    for (size_t j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (this->list_[j] < pivot)
        {
            std::swap(this->list_[i], this->list_[j]);
            this->swapList_.push_back(std::pair<size_t, size_t>(i, j));
            this->coloredList_.push_back(std::vector<size_t>{i, j, high});
            i++; // increment index of smaller element
        }
    }
    std::swap(this->list_[i], this->list_[high]);
    this->swapList_.push_back(std::pair<size_t, size_t>(i, high));
    this->coloredList_.push_back(std::vector<size_t>{i, high});
    return (i);
}

template<class T>
void QuickSort<T>::QuickSortFunc(size_t low, size_t high)
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
