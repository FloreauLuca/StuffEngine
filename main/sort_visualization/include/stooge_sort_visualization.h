#pragma once
#include "algo/sort/stooge_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class StoogeSortVisualization final : public SortVisualization
	{
	public:
		explicit StoogeSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "StoogeSort";
		}

		void SortList() override;
	private:
		algo::StoogeSort<int> stooge_sort_;
	};
}
