#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/stooge-sort/
namespace stuff::algo
{
template<Sortable T>
class StoogeSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
private:
	void StoogeSortFunc(int l, int h);
};
}
