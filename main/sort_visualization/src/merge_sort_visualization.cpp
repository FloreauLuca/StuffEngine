#include "merge_sort_visualization.h"

#include <vector>

namespace stuff
{
void MergeSortVisualization::SortList()
{
	merge_sort_.SetList(list_);
	auto start = std::chrono::system_clock::now();
	swap_pairs = merge_sort_.SortList();
	auto end = std::chrono::system_clock::now();
	sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	coloredList_ = merge_sort_.GetColoredList();
}
}
