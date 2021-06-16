#pragma once
#include "algo/sort/pancake_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class PancakeSortVisualization final : public SortVisualization
	{
	public:
		explicit PancakeSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "Pancake Sort";
		}

		void SortList() override;
	private:
		algo::PancakeSort<int> pancake_sort_;
	};
}
