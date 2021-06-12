#include "algo/sort/merge_sort.h"

namespace stuff::algo
{
template <Sortable T>
std::vector<std::pair<size_t, size_t>> MergeSort<T>::SortList()
{
	MergeSortFunc(0, this->listSize_ - 1);
	return this->swapList_;
}

template <Sortable T>
void MergeSort<T>::Merge(int start, int mid, int end)
{
	int start2 = mid + 1;

	// If the direct merge is already sorted
	if (this->list_[mid] <= this->list_[start2])
	{
		return;
	}

	// Two pointers to maintain start
	// of both arrays to merge
	while (start <= mid && start2 <= end)
	{
		// If element 1 is in right place
		if (this->list_[start] <= this->list_[start2])
		{
			start++;
		}
		else
		{
			T value = this->list_[start2];
			size_t index = start2;
			int switchPos = start2;
			// Shift all the elements between element 1
			// element 2, right by 1.
			while (index != start)
			{
				this->list_[index] = this->list_[index - 1];
				this->swapList_.push_back(std::pair<size_t, size_t>(index, index - 1));
				this->coloredList_.push_back(std::vector<size_t>{index, index - 1});
				if (index == start2)
				{
					switchPos = index - 1;
				}
				if (index - 1 == start2)
				{
					switchPos = index;
				}
				index--;
			}
			this->list_[start] = value; // ?????
			//swapList_.push_back(std::pair<size_t, size_t>(start, switchPos));

			// Update all the pointers
			start++;
			mid++;
			start2++;
		}
	}
}

template <Sortable T>
// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void MergeSort<T>::MergeSortFunc(int l, int r)
{
	if (l >= r)
	{
		return; //returns recursively
	}
	int m = l + (r - l) / 2;
	MergeSortFunc(l, m);
	MergeSortFunc(m + 1, r);
	Merge(l, m, r);
}
}
