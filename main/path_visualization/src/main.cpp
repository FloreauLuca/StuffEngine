#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "path_visualization.h"

int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 600, 600 });
	stuff::PathVisualization path_visualization(engine);
	engine.RegisterSystem(path_visualization);
	engine.StartEngine();
    return 0;
}
