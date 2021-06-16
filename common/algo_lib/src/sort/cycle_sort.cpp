#include "algo/sort/cycle_sort.h"

namespace stuff::algo
{
	template<Sortable T>
	std::vector<std::pair<size_t, size_t>> CycleSort<T>::SortList()
	{
		size_t i, j;
		bool swapped;
		for (i = 0; i < this->listSize_ - 1; i++)
		{
			swapped = false;
			for (j = 0; j < this->listSize_ - i - 1; j++)
			{
				if (this->list_[j] > this->list_[j + 1])
				{
					std::swap(this->list_[j], this->list_[j + 1]);
					this->swapList_.push_back(std::pair<size_t, size_t>(j, j + 1));
					this->coloredList_.push_back(std::vector<size_t>{j, j + 1});
					swapped = true;
				}
			}

			// IF no two elements were swapped by inner loop, then break
			if (swapped == false)
				break;
		}
		return this->swapList_;
	}
}
