#pragma once
#include "sort.h"
#include "engine/engine.h"
//https://www.geeksforgeeks.org/stooge-sort/
namespace stuff::algo
{
class StoogeSort final : public Sort
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
private:
	void StoogeSortFunc(int l, int h);
};
}
