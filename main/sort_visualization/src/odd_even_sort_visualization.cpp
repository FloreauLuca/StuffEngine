#include "odd_even_sort_visualization.h"

#include <vector>

namespace stuff
{
void OddEvenSortVisualization::SortList()
{
	odd_even_sort_.SetList(list_);
	auto start = std::chrono::system_clock::now();
	swapPairs_ = odd_even_sort_.SortList();
	auto end = std::chrono::system_clock::now();
	sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	coloredList_ = odd_even_sort_.GetColoredList();
}
}
