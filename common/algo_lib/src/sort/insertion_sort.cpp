#pragma once
#include "algo/sort/insertion_sort.h"

namespace stuff::algo
{
template <Sortable T>
std::vector<std::pair<size_t, size_t>> InsertionSort<T>::SortList()
{
	int i, j;
	T key;
	for (i = 1; i < this->listSize_; i++)
	{
		key = this->list_[i];
		int index_i = i;
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && this->list_[j] > key)
		{
			this->list_[j + 1] = this->list_[j];
			j = j - 1;
		}
		this->list_[j + 1] = key;
	}
	return this->swapList_;
}
}
