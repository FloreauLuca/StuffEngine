#pragma once
#include "sort.h"

namespace stuff::algo
{
template <Sortable T>
class CombSort final : public Sort<T>
{
public:
	using Sort<T>::SetList;
	std::vector<std::pair<size_t, size_t>> SortList();
protected:

	int GetNextGap(int gap);
};
}
