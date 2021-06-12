#pragma once
#include "sort.h"
#include "engine/engine.h"
//https://www.geeksforgeeks.org/selection-sort/
namespace stuff::algo
{
template<class T>
class SelectionSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
