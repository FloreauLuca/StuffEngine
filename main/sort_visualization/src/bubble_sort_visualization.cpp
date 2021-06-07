#include "bubble_sort_visualization.h"

#include <vector>

namespace stuff
{
void BubbleSortVisualization::SortList()
{
	bubble_sort_.SetList(list_);
	auto start = std::chrono::system_clock::now();
	swap_pairs = bubble_sort_.SortList();
	auto end = std::chrono::system_clock::now();
	sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	coloredList_ = bubble_sort_.GetColoredList();
}
}
