#pragma once
#include "algo/sort/bubble_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class BubbleSortVisualization final : public SortVisualization
{
public:
	explicit BubbleSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
		sortName_ = "Bubble Sort";
	}

	void SortList() override;
private:
	algo::BubbleSort<int> bubble_sort_;
};
}
