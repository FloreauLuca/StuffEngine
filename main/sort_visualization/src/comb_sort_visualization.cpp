#include "comb_sort_visualization.h"

#include <vector>

namespace stuff
{
void CombSortVisualization::SortList()
{
	comb_sort_.SetList(list_);
	swap_pairs = comb_sort_.SortList();
	coloredList_ = comb_sort_.GetColoredList();
}
}
