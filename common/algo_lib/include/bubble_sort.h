#pragma once
#include "sort.h"
#include "engine/engine.h"

namespace stuff::algo
{
class BubbleSort final : public Sort
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
};
}
