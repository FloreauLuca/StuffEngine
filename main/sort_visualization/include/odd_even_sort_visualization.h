#pragma once
#include "algo/sort/odd_even_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class OddEvenSortVisualization final : public SortVisualization
	{
	public:
		explicit OddEvenSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "OddEven Sort";
		}

		void SortList() override;
	private:
		algo::OddEvenSort<int> odd_even_sort_;
	};
}
