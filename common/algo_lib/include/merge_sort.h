#pragma once
#include "sort.h"
#include "engine/engine.h"

namespace stuff::algo
{
class MergeSort final : public Sort
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
	void Merge(int start, int mid, int end);
	void MergeSortFunc(int l, int r);
};
}