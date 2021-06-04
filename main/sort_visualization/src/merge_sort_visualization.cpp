#include "merge_sort_visualization.h"

#include <vector>

namespace stuff
{
void MergeSortVisualization::SortList()
{
	merge_sort_.SetList(list_);
	swap_pairs = merge_sort_.SortList();
	coloredList_ = merge_sort_.GetColoredList();
}
}
