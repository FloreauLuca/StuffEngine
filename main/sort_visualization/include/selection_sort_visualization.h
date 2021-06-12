#pragma once
#include "algo/sort/selection_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class SelectionSortVisualization final : public SortVisualization
	{
	public:
		explicit SelectionSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "SelectionSort";
		}

		void SortList() override;
	private:
		algo::SelectionSort<int> selection_sort_;
	};
}
