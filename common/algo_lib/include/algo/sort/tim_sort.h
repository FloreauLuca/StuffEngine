#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/timsort/

namespace stuff::algo
{
template<Sortable T>
class TimSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
