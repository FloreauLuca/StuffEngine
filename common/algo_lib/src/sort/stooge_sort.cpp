#pragma once
#include "algo/sort/stooge_sort.h"

namespace stuff::algo
{
	template<class T>
	std::vector<std::pair<size_t, size_t>> StoogeSort<T>::SortList()
	{
		StoogeSortFunc(0, this->listSize_ - 1);
		return this->swapList_;
	}

	template<class T>
	void StoogeSort<T>::StoogeSortFunc(int l, int h)
	{
		if (l >= h)
			return;

		// If first element is smaller than last,
		// swap them
		if (this->list_[l] > this->list_[h])
		{
			std::swap(this->list_[l], this->list_[h]);
			this->swapList_.push_back(std::pair<size_t, size_t>(l, h));
			this->coloredList_.push_back(std::vector<size_t>{(unsigned)l, (unsigned)h});
		}

		// If there are more than 2 elements in
		// the array
		if (h - l + 1 > 2) {
			int t = (h - l + 1) / 3;

			// Recursively sort first 2/3 elements
			StoogeSortFunc(l, h - t);

			// Recursively sort last 2/3 elements
			StoogeSortFunc(l + t, h);

			// Recursively sort first 2/3 elements
			// again to confirm
			StoogeSortFunc(l, h - t);
		}
	}
}
