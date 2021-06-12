#pragma once
#include "sort.h"
#include "engine/engine.h"
//https://www.geeksforgeeks.org/heap-sort/
namespace stuff::algo
{
template<class T>
class HeapSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
private:
	void heapify(int end, int i);
};
}
