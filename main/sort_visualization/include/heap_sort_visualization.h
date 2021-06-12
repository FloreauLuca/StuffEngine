#pragma once
#include "algo/sort/heap_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class HeapSortVisualization final : public SortVisualization
	{
	public:
		explicit HeapSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "Heap Sort";
		}

		void SortList() override;
	private:
		algo::HeapSort heap_sort_;
	};
}
