#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "steering_visualization.h"

int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 600, 600 });
	stuff::SteeringVisualization steering_visualization(engine);
	engine.RegisterSystem(steering_visualization);
	engine.StartEngine();
	return 0;
}
