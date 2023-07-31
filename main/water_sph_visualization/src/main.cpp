#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "water_sph_visualization.h"

int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 900, 900 });
	//engine.GetGraphics().SetWindowSize({ 450, 800 });
	stuff::WaterSphVisualization water_sph_visualization(engine);
	engine.RegisterSystem(water_sph_visualization);
	engine.StartEngine();
	return 0;
}
