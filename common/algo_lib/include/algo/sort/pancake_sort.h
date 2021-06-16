#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/pancake-sorting/

namespace stuff::algo
{
template<Sortable T>
class PancakeSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
private:
	void Flip(size_t i);
	unsigned FindMax(size_t n);
};
}
