#pragma once
#include "sort.h"

namespace stuff::algo
{
template<Sortable T>
class MergeSort final : public Sort<T>
{
public:
	using Sort<T>::SetList;
	std::vector<std::pair<size_t, size_t>> SortList();
private:
	void Merge(int start, int mid, int end);
	void MergeSortFunc(int l, int r);
};
}
