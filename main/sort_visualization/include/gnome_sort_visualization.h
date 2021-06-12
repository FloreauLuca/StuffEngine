#pragma once
#include "algo/sort/gnome_sort.h"
#include "sort_visualization.h"

namespace stuff
{
	class GnomeSortVisualization final : public SortVisualization
	{
	public:
		explicit GnomeSortVisualization(Engine& engine)
			: SortVisualization(engine)
		{
			sortName_ = "Gnome Sort";
		}

		void SortList() override;
	private:
		algo::GnomeSort<int> gnome_sort_;
	};
}
