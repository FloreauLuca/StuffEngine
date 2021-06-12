#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/odd-even-sort-brick-sort/
namespace stuff::algo
{
template<Sortable T>
class OddEvenSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
