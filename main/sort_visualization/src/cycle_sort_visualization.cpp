#include "cycle_sort_visualization.h"

#include <vector>

namespace stuff
{
void CycleSortVisualization::SortList()
{
	cycle_sort_.SetList(list_);
	auto start = std::chrono::system_clock::now();
	swapPairs_ = cycle_sort_.SortList();
	auto end = std::chrono::system_clock::now();
	sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	coloredList_ = cycle_sort_.GetColoredList();
}
}
