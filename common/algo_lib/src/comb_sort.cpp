#include "algo/sort/comb_sort.h"

namespace stuff::algo
{
template <class T>
int CombSort<T>::GetNextGap(int gap)
{
	// Shrink gap by Shrink factor
	gap = (gap * 10) / 13;

	if (gap < 1)
		return 1;
	return gap;
}

template <class T>
std::vector<std::pair<size_t, size_t>> CombSort<T>::SortList()
{
	// Initialize gap
	int gap = this->listSize_;

	// Initialize swapped as true to make sure that
	// loop runs
	bool swapped = true;

	// Keep running while gap is more than 1 and last
	// iteration caused a swap
	while (gap != 1 || swapped == true)
	{
		// Find next gap
		gap = GetNextGap(gap);

		// Initialize swapped as false so that we can
		// check if swap happened or not
		swapped = false;

		// Compare all elements with current gap
		for (size_t i = 0; i < this->listSize_ - gap; i++)
		{
			if (this->list_[i] > this->list_[i + gap])
			{
				std::swap(this->list_[i], this->list_[i + gap]);
				this->swapList_.push_back(std::pair<size_t, size_t>(i, i + gap));
				this->coloredList_.push_back(std::vector<size_t>{i, i + gap});
				swapped = true;
			}
		}
	}
	return this->swapList_;
}
}
