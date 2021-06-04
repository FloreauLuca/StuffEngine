#pragma once
#include "cocktail_sort.h"
#include "sort_visualization.h"

namespace stuff
{
class CocktailSortVisualization final : public SortVisualization
{
public:
	explicit CocktailSortVisualization(Engine& engine)
		: SortVisualization(engine)
	{
	}

	void SortList() override;
private:
	algo::CocktailSort cocktail_sort_;
};
}
