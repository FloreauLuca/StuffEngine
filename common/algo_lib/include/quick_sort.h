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
	size_t Partition(int low, int high);
	void QuickSortFunc(int low, int high);
	std::vector<std::pair<size_t, size_t>> swapList_;
};
}

