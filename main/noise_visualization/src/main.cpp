#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"

#include "perlin_noise_steps.h"
#include "perlin_noise_parameters.h"
#include "polar_noise_circle.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 900, 900 });
	stuff::PolarNoiseCircle polar_noise_circle(engine);
	engine.RegisterSystem(polar_noise_circle);
	engine.StartEngine();
	stuff::PerlinNoiseParameters perlin_noise_parameters(engine);
	engine.RegisterSystem(perlin_noise_parameters);
	engine.StartEngine();
	stuff::PerlinNoiseSteps perlin_noise_steps(engine);
	engine.RegisterSystem(perlin_noise_parameters);
	engine.StartEngine();
    return 0;
}
