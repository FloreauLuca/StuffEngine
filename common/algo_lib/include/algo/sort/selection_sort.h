#pragma once
#include "sort.h"
#include "engine/engine.h"
//https://www.geeksforgeeks.org/selection-sort/
namespace stuff::algo
{
class SelectionSort final : public Sort
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
};
}
