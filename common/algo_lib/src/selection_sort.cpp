#pragma once
#include "algo/sort/selection_sort.h"

namespace stuff::algo
{
	std::vector<std::pair<size_t, size_t>> SelectionSort::SortList()
	{
        int i, j, min_idx;

        // One by one move boundary of unsorted subarray
        for (i = 0; i < listSize_ - 1; i++)
        {
            // Find the minimum element in unsorted array
            min_idx = i;
            for (j = i + 1; j < listSize_; j++)
                if (list_[j] < list_[min_idx])
                    min_idx = j;

            // Swap the found minimum element with the first element
            std::swap(list_[min_idx], list_[i]);
            swapList_.push_back(std::pair<size_t, size_t>(min_idx, i));
            coloredList_.push_back(std::vector<size_t>{(unsigned)min_idx, (unsigned)i});
        }
		return swapList_;
	}
}
