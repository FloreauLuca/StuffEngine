#pragma once
#include "algo/sort/bogo_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class BogoSortVisualization final : public SortVisualization
{
public:
	explicit BogoSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
		sortName_ = "Bogo Sort";
	}

	void SortList() override;
private:
	algo::BogoSort<int> bogo_sort_;
};
}
