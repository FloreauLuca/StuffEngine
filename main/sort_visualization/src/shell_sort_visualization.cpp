#include "shell_sort_visualization.h"

#include <vector>

namespace stuff
{
	void ShellSortVisualization::SortList()
	{
		shell_sort_.SetList(list_);
		auto start = std::chrono::system_clock::now();
		swap_pairs = shell_sort_.SortList();
		auto end = std::chrono::system_clock::now();
		sortTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		coloredList_ = shell_sort_.GetColoredList();
	}
}