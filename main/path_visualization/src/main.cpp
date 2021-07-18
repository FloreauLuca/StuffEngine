#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "map_visualization.h"

int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 600, 600 });
	stuff::MapVisualization map_visualization(engine);
	engine.RegisterSystem(map_visualization);
	engine.StartEngine();
    return 0;
}
