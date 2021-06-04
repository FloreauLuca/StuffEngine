#pragma once
#include "sort.h"
#include "engine/engine.h"

namespace stuff::algo
{
class CombSort final : public Sort
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
protected:

	int GetNextGap(int gap);
};
}
