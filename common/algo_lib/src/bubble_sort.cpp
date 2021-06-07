#include "algo/sort/bubble_sort.h"

namespace stuff::algo
{
std::vector<std::pair<size_t, size_t>> BubbleSort::SortList()
{
	size_t i, j;
	bool swapped;
	for (i = 0; i < listSize_ - 1; i++)
	{
		swapped = false;
		for (j = 0; j < listSize_ - i - 1; j++)
		{
			if (list_[j] > list_[j + 1])
			{
				std::swap(list_[j], list_[j + 1]);
				swapList_.push_back(std::pair<size_t, size_t>(j, j + 1));
				coloredList_.push_back(std::vector<size_t>{j, j + 1});
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
	return swapList_;
}
}
