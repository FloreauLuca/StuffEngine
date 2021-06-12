#pragma once
#include "algo/sort/cocktail_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class CocktailSortVisualization final : public SortVisualization
{
public:
	explicit CocktailSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
		sortName_ = "Cocktail Sort";
	}

	void SortList() override;
private:
	algo::CocktailSort<int> cocktail_sort_;
};
}
