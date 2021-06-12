#pragma once
#include "algo/sort/heap_sort.h"

namespace stuff::algo
{
	std::vector<std::pair<size_t, size_t>> HeapSort::SortList()
	{
		// Build heap (rearrange array)
		for (int i = listSize_ / 2 - 1; i >= 0; i--)
			heapify(listSize_, i);

		// One by one extract an element from heap
		for (int i = listSize_ - 1; i > 0; i--) {
			// Move current root to end
			std::swap(list_[0], list_[i]);
			swapList_.push_back(std::pair<size_t, size_t>(0, i));
			coloredList_.push_back(std::vector<size_t>{0, (unsigned)i});

			// call max heapify on the reduced heap
			heapify(i, 0);
		}
		return swapList_;
	}

	void HeapSort::heapify(int end,int i)
	{
		int largest = i; // Initialize largest as root
		int l = 2 * i + 1; // left = 2*i + 1
		int r = 2 * i + 2; // right = 2*i + 2

		// If left child is larger than root
		if (l < end && list_[l] > list_[largest])
			largest = l;

		// If right child is larger than largest so far
		if (r < end && list_[r] > list_[largest])
			largest = r;

		// If largest is not root
		if (largest != i) {
			std::swap(list_[i], list_[largest]);
			swapList_.push_back(std::pair<size_t, size_t>(i, largest));
			coloredList_.push_back(std::vector<size_t>{(unsigned)i, (unsigned)largest});

			// Recursively heapify the affected sub-tree
			heapify(end, largest);
		}
	}
}
