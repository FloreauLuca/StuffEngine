#pragma once
#include "sort.h"
#include "engine/engine.h"
//https://www.geeksforgeeks.org/heap-sort/
namespace stuff::algo
{
class HeapSort final : public Sort
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
private:
	void heapify(int end, int i);
};
}
