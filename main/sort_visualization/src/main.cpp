#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "bubble_sort_visualization.h"
#include "quick_sort_visualization.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	stuff::QuickSortVisualization quick_sort_visualization(engine);
	engine.RegisterSystem(quick_sort_visualization);
	engine.StartEngine();
	stuff::BubbleSortVisualization bubble_sort_visualization(engine);
	engine.RegisterSystem(bubble_sort_visualization);
	engine.StartEngine();
    return 0;
}
