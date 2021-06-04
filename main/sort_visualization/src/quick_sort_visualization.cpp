#include "quick_sort_visualization.h"

#include <vector>

namespace stuff
{
void QuickSortVisualization::SortList()
{
	quick_sort_.SetList(list_);
	swap_pairs = quick_sort_.SortList();
	coloredList_ = quick_sort_.GetColoredList();
}
}
