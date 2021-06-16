#include "algo/sort/pancake_sort.h"

namespace stuff::algo
{
	template<Sortable T>
	std::vector<std::pair<size_t, size_t>> PancakeSort<T>::SortList()
	{
		for (int curr_size = this->listSize_; curr_size > 1;--curr_size)
		{
			int mi = FindMax(curr_size);
			
			if (mi != curr_size - 1) {

				Flip(mi);
				
				Flip(curr_size - 1);
			}
		}
		return this->swapList_;
	}

	template <Sortable T>
	void PancakeSort<T>::Flip(size_t i)
	{
		size_t start = 0;
		while (start < i) {
			std::swap(this->list_[start], this->list_[i]);
			this->swapList_.push_back(std::pair<size_t, size_t>(start, i));
			this->coloredList_.push_back(std::vector<size_t>{start, i});
			start++;
			i--;
		}
	}

	template <Sortable T>
	unsigned PancakeSort<T>::FindMax(size_t n)
	{

		size_t mi, i;
		for (mi = 0, i = 0; i < n; ++i)
			if (this->list_[i] > this->list_[mi])
				mi = i;
		return mi;
	}
}
