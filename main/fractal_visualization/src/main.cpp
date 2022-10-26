#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"

#include "fractal_visualization.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 900, 900 });
	stuff::FractalVisualization fractal_visualization(engine);
	engine.RegisterSystem(fractal_visualization);
	engine.StartEngine();
    return 0;
}
