#pragma once
#include "merge_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class MergeSortVisualization final : public SortVisualization
	{
	public:
		explicit MergeSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
		}

		void SortList() override;
	private:
		algo::MergeSort<int> merge_sort_;
	};
}
