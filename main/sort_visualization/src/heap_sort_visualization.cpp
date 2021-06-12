#include "heap_sort_visualization.h"

#include <vector>

namespace stuff
{
void HeapSortVisualization::SortList()
{
	heap_sort_.SetList(list_);
	auto start = std::chrono::system_clock::now();
	swap_pairs = heap_sort_.SortList();
	auto end = std::chrono::system_clock::now();
	sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	coloredList_ = heap_sort_.GetColoredList();
}
}
