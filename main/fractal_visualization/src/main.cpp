#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"

#include "fractal_visualization.h"
#include <julia_fractal.h>
#include <mandelbrot_fractal.h>
#include <newton_fractal.h>

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 450, 800 });
	//engine.GetGraphics().SetWindowSize({ 750, 750 });
	stuff::JuliaFractal julia_fractal = stuff::JuliaFractal(engine);
	stuff::FractalVisualization julia_fractal_visualization(engine, julia_fractal);
	engine.RegisterSystem(julia_fractal_visualization);
	engine.StartEngine();
	stuff::MandelbrotFractal mandelbrot_fractal = stuff::MandelbrotFractal(engine);
	stuff::FractalVisualization mandelbrot_fractal_visualization(engine, mandelbrot_fractal);
	engine.RegisterSystem(mandelbrot_fractal_visualization);
	engine.StartEngine();
	stuff::NewtonFractal newton_fractal = stuff::NewtonFractal(engine);
	stuff::FractalVisualization newton_ractal_visualization(engine, newton_fractal);
	engine.RegisterSystem(newton_ractal_visualization);
	engine.StartEngine();
    return 0;
}
