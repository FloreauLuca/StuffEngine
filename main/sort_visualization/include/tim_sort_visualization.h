#pragma once
#include "algo/sort/tim_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class TimSortVisualization final : public SortVisualization
	{
	public:
		explicit TimSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "Tim Sort";
		}

		void SortList() override;
	private:
		algo::TimSort<int> tim_sort_;
	};
}
