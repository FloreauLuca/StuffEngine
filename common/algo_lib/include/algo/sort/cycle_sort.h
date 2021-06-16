#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/cycle-sort/

namespace stuff::algo
{
template<Sortable T>
class CycleSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
