#pragma once
#include "algo/sort/cycle_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class CycleSortVisualization final : public SortVisualization
{
public:
	explicit CycleSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
		sortName_ = "Cycle Sort";
	}

	void SortList() override;
private:
	algo::CycleSort<int> cycle_sort_;
};
}
