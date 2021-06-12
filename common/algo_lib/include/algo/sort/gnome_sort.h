#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/gnome-sort-a-stupid-one/
namespace stuff::algo
{
template <Sortable T>
class GnomeSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
