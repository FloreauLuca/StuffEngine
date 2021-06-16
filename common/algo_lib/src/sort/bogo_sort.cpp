#include "algo/sort/bogo_sort.h"

namespace stuff::algo
{
	template<Sortable T>
	std::vector<std::pair<size_t, size_t>> BogoSort<T>::SortList()
	{

		// if array is not sorted then shuffle
		// the array again
		while (!IsSorted())
			Shuffle();
		
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

	template <Sortable T>
	bool BogoSort<T>::IsSorted()
	{
		for (int i = 0; i < this->listSize_ - 1; ++i)
		{
			if (this->list_[i] > this->list_[i + 1])
			{
				return false;
			}
		}
		return true;
	}

	template <Sortable T>
	void BogoSort<T>::Shuffle()
	{
		for (size_t i = 0; i < this->listSize_; i++)
		{
			size_t randIndex = rand() % this->listSize_;
			std::swap(this->list_[i], this->list_[randIndex]);
			this->swapList_.push_back(std::pair<size_t, size_t>(i, randIndex));
			this->coloredList_.push_back(std::vector<size_t>{i, randIndex});
		}
	}
}
