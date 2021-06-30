#pragma once
#include "algo/sort/shell_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class ShellSortVisualization final : public SortVisualization
{
public:
	explicit ShellSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
		sortName_ = "Shell Sort";
	}

	void SortList() override;
private:
	algo::ShellSort<int> shell_sort_;
};
}
