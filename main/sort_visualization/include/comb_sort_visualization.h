#pragma once
#include "algo/sort/comb_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class CombSortVisualization final : public SortVisualization
{
public:
	explicit CombSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
		sortName_ = "Comb Sort";
	}

	void SortList() override;
private:
	algo::CombSort<int> comb_sort_;
};
}
