#pragma once
#include "algo/sort/odd_even_sort.h"

namespace stuff::algo
{
	std::vector<std::pair<size_t, size_t>> OddEvenSort::SortList()
	{
        bool isSorted = false; // Initially array is unsorted

        while (!isSorted)
        {
            isSorted = true;

            // Perform Bubble sort on odd indexed element
            for (int i = 1; i <= listSize_ - 2; i = i + 2)
            {
                if (list_[i] > list_[i + 1])
                {
	                std::swap(list_[i], list_[i + 1]);
                    swapList_.push_back(std::pair<size_t, size_t>(i, i+1));
                    coloredList_.push_back(std::vector<size_t>{(unsigned)i, (unsigned)i+1});
                    isSorted = false;
                }
            }

            // Perform Bubble sort on even indexed element
            for (int i = 0; i <= listSize_ - 2; i = i + 2)
            {
                if (list_[i] > list_[i + 1])
                {
	                std::swap(list_[i], list_[i + 1]);
                    swapList_.push_back(std::pair<size_t, size_t>(i, i + 1));
                    coloredList_.push_back(std::vector<size_t>{(unsigned)i, (unsigned)i + 1});
                    isSorted = false;
                }
            }
        }
		return swapList_;
	}
}
