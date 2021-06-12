#pragma once
#include "algo/sort/merge_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class MergeSortVisualization final : public SortVisualization
	{
	public:
		explicit MergeSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "Merge Sort";
		}

		void SortList() override;
	private:
		algo::MergeSort<int> merge_sort_;
	};
}
