#pragma once
#include "sort.h"
#include "engine/engine.h"

namespace stuff::algo
{
class QuickSort final : public Sort
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
private:
	int Partition(size_t low, size_t high);
	void QuickSortFunc(size_t low, size_t high);
};
}

