#pragma once
#include "algo/sort/odd_even_sort.h"

namespace stuff::algo
{
    template<class T>
	std::vector<std::pair<size_t, size_t>> OddEvenSort<T>::SortList()
	{
        bool isSorted = false; // Initially array is unsorted

        while (!isSorted)
        {
            isSorted = true;

            // Perform Bubble sort on odd indexed element
            for (int i = 1; i <= this->listSize_ - 2; i = i + 2)
            {
                if (this->list_[i] > this->list_[i + 1])
                {
	                std::swap(this->list_[i], this->list_[i + 1]);
                    this->swapList_.push_back(std::pair<size_t, size_t>(i, i+1));
                    this->coloredList_.push_back(std::vector<size_t>{(unsigned)i, (unsigned)i+1});
                    isSorted = false;
                }
            }

            // Perform Bubble sort on even indexed element
            for (int i = 0; i <= this->listSize_ - 2; i = i + 2)
            {
                if (this->list_[i] > this->list_[i + 1])
                {
	                std::swap(this->list_[i], this->list_[i + 1]);
                    this->swapList_.push_back(std::pair<size_t, size_t>(i, i + 1));
                    this->coloredList_.push_back(std::vector<size_t>{(unsigned)i, (unsigned)i + 1});
                    isSorted = false;
                }
            }
        }
		return this->swapList_;
	}
}
