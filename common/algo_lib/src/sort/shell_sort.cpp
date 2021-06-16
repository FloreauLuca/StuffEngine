#include "algo/sort/shell_sort.h"

namespace stuff::algo
{
	template<Sortable T>
	std::vector<std::pair<size_t, size_t>> ShellSort<T>::SortList()
	{
        // Start with a big gap, then reduce the gap
        for (int gap = this->listSize_ / 2; gap > 0; gap /= 2)
        {
            // Do a gapped insertion sort for this gap size.
            // The first gap elements a[0..gap-1] are already in gapped order
            // keep adding one more element until the entire array is
            // gap sorted
            for (int i = gap; i < this->listSize_; i += 1)
            {
                // add a[i] to the elements that have been gap sorted
                // save a[i] in temp and make a hole at position i
                int temp = this->list_[i];

                // shift earlier gap-sorted elements up until the correct
                // location for a[i] is found
                int j;
                for (j = i; j >= gap && this->list_[j - gap] > temp; j -= gap)
                    std::swap(this->list_[j], this->list_[j - gap]);

                //  put temp (the original a[i]) in its correct location
                //arr[j] = temp;
            }
        }
		return this->swapList_;
	}
}
