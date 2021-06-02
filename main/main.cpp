#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "sfml_test.h"
#include "sort_visualization.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	stuff::SfmlTest sfml_test(engine);
	stuff::SortVisualization sort_visualization(engine);
	engine.RegisterSystem(sort_visualization);
	engine.StartEngine();
    return 0;
}
