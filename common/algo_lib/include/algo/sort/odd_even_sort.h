#pragma once
#include "sort.h"
#include "engine/engine.h"
//https://www.geeksforgeeks.org/odd-even-sort-brick-sort/
namespace stuff::algo
{
template<class T>
class OddEvenSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
