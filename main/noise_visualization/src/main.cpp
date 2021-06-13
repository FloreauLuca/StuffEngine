#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"

#include "perlin_noise_steps.h"
#include "perlin_noise_parameters.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 900, 900 });
	stuff::PerlinNoiseParameters perlin_noise_parameters(engine);
	engine.RegisterSystem(perlin_noise_parameters);
	engine.StartEngine();
	stuff::PerlinNoiseSteps perlin_noise_steps(engine);
	engine.RegisterSystem(perlin_noise_parameters);
	engine.StartEngine();
    return 0;
}
