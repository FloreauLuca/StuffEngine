#pragma once
#include "algo/sort/selection_sort.h"

namespace stuff::algo
{
    template<class T>
	std::vector<std::pair<size_t, size_t>> SelectionSort<T>::SortList()
	{
        int i, j, min_idx;

        // One by one move boundary of unsorted subarray
        for (i = 0; i < this->listSize_ - 1; i++)
        {
            // Find the minimum element in unsorted array
            min_idx = i;
            for (j = i + 1; j < this->listSize_; j++)
                if (this->list_[j] < this->list_[min_idx])
                    min_idx = j;

            // Swap the found minimum element with the first element
            std::swap(this->list_[min_idx], this->list_[i]);
            this->swapList_.push_back(std::pair<size_t, size_t>(min_idx, i));
            this->coloredList_.push_back(std::vector<size_t>{(unsigned)min_idx, (unsigned)i});
        }
		return this->swapList_;
	}
}
