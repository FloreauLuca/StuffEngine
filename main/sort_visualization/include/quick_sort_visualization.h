#pragma once
#include "algo/sort/quick_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class QuickSortVisualization final : public SortVisualization
{
public:
	explicit QuickSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
		sortName_ = "Quick Sort";
	}

	void SortList() override;
private:
	algo::QuickSort<int> quick_sort_;
};
}
