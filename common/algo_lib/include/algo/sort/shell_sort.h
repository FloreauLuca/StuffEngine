#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/shellsort/

namespace stuff::algo
{
template<Sortable T>
class ShellSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
