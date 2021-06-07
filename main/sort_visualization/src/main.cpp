#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "bubble_sort_visualization.h"
#include "quick_sort_visualization.h"
#include "cocktail_sort_visualization.h"
#include "comb_sort_visualization.h"
#include "merge_sort_visualization.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	//stuff::CombSortVisualization comb_sort_visualization(engine);
	//engine.RegisterSystem(comb_sort_visualization);
	//engine.StartEngine();
	stuff::CocktailSortVisualization cocktail_sort_visualization(engine);
	engine.RegisterSystem(cocktail_sort_visualization);
	engine.StartEngine();
	stuff::MergeSortVisualization merge_sort_visualization(engine);
	engine.RegisterSystem(merge_sort_visualization);
	engine.StartEngine();
	stuff::QuickSortVisualization quick_sort_visualization(engine);
	engine.RegisterSystem(quick_sort_visualization);
	engine.StartEngine();
	stuff::BubbleSortVisualization bubble_sort_visualization(engine);
	engine.RegisterSystem(bubble_sort_visualization);
	engine.StartEngine();
    return 0;
}
