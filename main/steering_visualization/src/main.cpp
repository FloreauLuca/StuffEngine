#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


#include "flocking_visualization.h"
#include "engine/engine.h"
#include "steering_visualization.h"

int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 450, 800 });
	stuff::FlockingVisualization flocking_visualization(engine);
	engine.RegisterSystem(flocking_visualization);
	engine.StartEngine();
	stuff::SteeringVisualization steering_visualization(engine);
	engine.RegisterSystem(steering_visualization);
	engine.StartEngine();
	return 0;
}
