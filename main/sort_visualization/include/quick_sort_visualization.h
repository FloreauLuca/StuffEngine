#pragma once
#include "quick_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class QuickSortVisualization final : public SortVisualization
{
public:
	explicit QuickSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
	}

	void SortList() override;
private:
	algo::QuickSort quick_sort_;
};
}
