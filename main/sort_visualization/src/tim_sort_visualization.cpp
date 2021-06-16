#include "tim_sort_visualization.h"

#include <vector>

namespace stuff
{
	void TimSortVisualization::SortList()
	{
		tim_sort_.SetList(list_);
		auto start = std::chrono::system_clock::now();
		swap_pairs = tim_sort_.SortList();
		auto end = std::chrono::system_clock::now();
		sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		coloredList_ = tim_sort_.GetColoredList();
	}
}
