#include "quick_sort_visualization.h"

#include <vector>

namespace stuff
{
void QuickSortVisualization::SortList()
{
	quick_sort_.SetList(list_);
	auto start = std::chrono::system_clock::now();
	swapPairs_ = quick_sort_.SortList();
	auto end = std::chrono::system_clock::now();
	sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	coloredList_ = quick_sort_.GetColoredList();
}
}
