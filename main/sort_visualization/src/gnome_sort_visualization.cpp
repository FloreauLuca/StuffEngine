#include "gnome_sort_visualization.h"

#include <vector>

namespace stuff
{
void GnomeSortVisualization::SortList()
{
	gnome_sort_.SetList(list_);
	auto start = std::chrono::system_clock::now();
	swap_pairs = gnome_sort_.SortList();
	auto end = std::chrono::system_clock::now();
	sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	coloredList_ = gnome_sort_.GetColoredList();
}
}
