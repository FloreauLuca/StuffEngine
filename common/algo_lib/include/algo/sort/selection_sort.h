#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/selection-sort/
namespace stuff::algo
{
template<Sortable T>
class SelectionSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
