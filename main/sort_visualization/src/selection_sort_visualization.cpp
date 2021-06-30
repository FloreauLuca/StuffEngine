#include "selection_sort_visualization.h"

#include <vector>

namespace stuff
{
void SelectionSortVisualization::SortList()
{
	selection_sort_.SetList(list_);
	auto start = std::chrono::system_clock::now();
	swapPairs_ = selection_sort_.SortList();
	auto end = std::chrono::system_clock::now();
	sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	coloredList_ = selection_sort_.GetColoredList();
}
}
