#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "bubble_sort_visualization.h"
#include "quick_sort_visualization.h"
#include "cocktail_sort_visualization.h"
#include "comb_sort_visualization.h"
#include "merge_sort_visualization.h"
#include "selection_sort_visualization.h"
#include "stooge_sort_visualization.h"
#include "heap_sort_visualization.h"
#include "odd_even_sort_visualization.h"
#include "insertion_sort_visualization.h"
#include "gnome_sort_visualization.h"

int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 600, 600 });
	stuff::GnomeSortVisualization gnome_sort_visualization(engine);
	engine.RegisterSystem(gnome_sort_visualization);
	engine.StartEngine();
	//stuff::InsertionSortVisualization insertion_sort_visualization(engine);
	//engine.RegisterSystem(insertion_sort_visualization);
	//engine.StartEngine();
	stuff::OddEvenSortVisualization odd_even_sort_visualization(engine);
	engine.RegisterSystem(odd_even_sort_visualization);
	engine.StartEngine();
	stuff::HeapSortVisualization heap_sort_visualization(engine);
	engine.RegisterSystem(heap_sort_visualization);
	engine.StartEngine();
	stuff::StoogeSortVisualization stooge_sort_visualization(engine);
	engine.RegisterSystem(stooge_sort_visualization);
	engine.StartEngine();
	stuff::SelectionSortVisualization selection_sort_visualization(engine);
	engine.RegisterSystem(selection_sort_visualization);
	engine.StartEngine();
	stuff::CombSortVisualization comb_sort_visualization(engine);
	engine.RegisterSystem(comb_sort_visualization);
	engine.StartEngine();
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
