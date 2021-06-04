#pragma once
#include "comb_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class CombSortVisualization final : public SortVisualization
{
public:
	explicit CombSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
	}

	void SortList() override;
private:
	algo::CombSort comb_sort_;
};
}