#pragma once
#include "bubble_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class BubbleSortVisualization final : public SortVisualization
{
public:
	explicit BubbleSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
	}

	void SortList() override;
private:
	algo::BubbleSort bubble_sort_;
};
}