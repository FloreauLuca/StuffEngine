#pragma once
#include "algo/sort/heap_sort.h"

namespace stuff::algo
{
template <Sortable T>
std::vector<std::pair<size_t, size_t>> HeapSort<T>::SortList()
{
	// Build heap (rearrange array)
	for (int i = this->listSize_ / 2 - 1; i >= 0; i--)
		heapify(this->listSize_, i);

	// One by one extract an element from heap
	for (int i = this->listSize_ - 1; i > 0; i--)
	{
		// Move current root to end
		std::swap(this->list_[0], this->list_[i]);
		this->swapList_.push_back(std::pair<size_t, size_t>(0, i));
		this->coloredList_.push_back(std::vector<size_t>{0, (unsigned)i});

		// call max heapify on the reduced heap
		heapify(i, 0);
	}
	return this->swapList_;
}

template <Sortable T>
void HeapSort<T>::heapify(int end, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < end && this->list_[l] > this->list_[largest])
		largest = l;

	// If right child is larger than largest so far
	if (r < end && this->list_[r] > this->list_[largest])
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		std::swap(this->list_[i], this->list_[largest]);
		this->swapList_.push_back(std::pair<size_t, size_t>(i, largest));
		this->coloredList_.push_back(std::vector<size_t>{(unsigned)i, (unsigned)largest});

		// Recursively heapify the affected sub-tree
		heapify(end, largest);
	}
}
}
