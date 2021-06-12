#pragma once
#include "algo/sort/insertion_sort.h"

namespace stuff::algo
{
	std::vector<std::pair<size_t, size_t>> InsertionSort::SortList()
	{
        int i, key, j;
        for (i = 1; i < listSize_; i++)
        {
            key = list_[i];
            int index_i = i;
            j = i - 1;

            /* Move elements of arr[0..i-1], that are
            greater than key, to one position ahead
            of their current position */
            while (j >= 0 && list_[j] > key)
            {
                list_[j + 1] = list_[j];
                j = j - 1;
            }
            list_[j + 1] = key;
        }
		return swapList_;
	}
}
