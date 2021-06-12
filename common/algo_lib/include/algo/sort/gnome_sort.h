#pragma once
#include "sort.h"
#include "engine/engine.h"
//https://www.geeksforgeeks.org/gnome-sort-a-stupid-one/
namespace stuff::algo
{
class GnomeSort final : public Sort
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
};
}
