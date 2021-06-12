#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/insertion-sort/
namespace stuff::algo
{
template<Sortable T>
class InsertionSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
