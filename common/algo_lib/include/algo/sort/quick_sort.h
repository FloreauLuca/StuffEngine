#pragma once
#include "sort.h"

namespace stuff::algo
{
template<Sortable T>
class QuickSort final : public Sort<T>
{
public:
	using Sort<T>::SetList;
	std::vector<std::pair<size_t, size_t>> SortList();
private:
	int Partition(size_t low, size_t high);
	void QuickSortFunc(size_t low, size_t high);
};
}

