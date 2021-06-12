#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/heap-sort/
namespace stuff::algo
{
template <Sortable T>
class HeapSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
private:
	void heapify(int end, int i);
};
}
