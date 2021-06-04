#include "cocktail_sort_visualization.h"

#include <vector>

namespace stuff
{
void CocktailSortVisualization::SortList()
{
	cocktail_sort_.SetList(list_);
	swap_pairs = cocktail_sort_.SortList();
	coloredList_ = cocktail_sort_.GetColoredList();
}
}
