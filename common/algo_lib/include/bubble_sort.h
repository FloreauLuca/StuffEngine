#pragma once
#include "sort.h"
#include "engine/engine.h"

namespace stuff::algo
{
	template<class T>
class BubbleSort final : public Sort<T>
{
public:
	std::vector<std::pair<size_t, size_t>> SortList() override;
};
}
