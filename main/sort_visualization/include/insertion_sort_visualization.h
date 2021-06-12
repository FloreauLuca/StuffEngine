#pragma once
#include "algo/sort/insertion_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class InsertionSortVisualization final : public SortVisualization
	{
	public:
		explicit InsertionSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "Insertion Sort";
		}

		void SortList() override;
	private:
		algo::InsertionSort<int> insertion_sort_;
	};
}
