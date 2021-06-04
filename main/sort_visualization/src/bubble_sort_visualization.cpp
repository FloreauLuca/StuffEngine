#include "bubble_sort_visualization.h"

#include <vector>

namespace stuff
{
void BubbleSortVisualization::SortList()
{
	bubble_sort_.SetList(list_);
	swap_pairs = bubble_sort_.SortList();
	coloredList_ = bubble_sort_.GetColoredList();
}
}
