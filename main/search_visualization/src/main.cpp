#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "search_visualization.h"
#include "engine/engine.h"

int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 900, 900 });
	stuff::SearchVisualization bubble_sort_visualization(engine);
	engine.RegisterSystem(bubble_sort_visualization);
	engine.StartEngine();
    return 0;
}
