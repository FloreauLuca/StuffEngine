#pragma once
#include "sort.h"
#include "engine/engine.h"
//https://www.geeksforgeeks.org/stooge-sort/
namespace stuff::algo
{
template<class T>
class StoogeSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
private:
	void StoogeSortFunc(int l, int h);
};
}
