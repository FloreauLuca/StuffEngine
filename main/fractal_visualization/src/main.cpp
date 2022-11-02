#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"

#include <camera.h>
#include "fractal_visualization.h"
#include <julia_fractal.h>
#include <mandelbrot_fractal.h>
#include <newton_fractal.h>

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	//engine.GetGraphics().SetWindowSize({ (unsigned)(567 * 1.0f) ,  (unsigned)(1008 * 1.0f) });
	engine.GetGraphics().SetWindowSize({ 1920, 1000 });
	std::cout << engine.GetGraphics().GetWindowSize().x << engine.GetGraphics().GetWindowSize().y << std::endl;
	//engine.GetGraphics().SetWindowSize({ 750, 750 });
	{
		std::vector<stuff::CameraParameters> cameraParameters_julia = {
			stuff::CameraParameters{ 4.0, sf::Vector2d(0.0, 0.0) },
			stuff::CameraParameters{ 0.0001, sf::Vector2d(0.374128960655082, 0.019155970762622) }
		};
		stuff::Camera camera_julia = stuff::Camera(0.1, 5.0, 0.00000000000015, cameraParameters_julia);
		stuff::JuliaFractal julia_fractal = stuff::JuliaFractal(engine, sf::Vector2d(0.323, -0.562));
		stuff::FractalVisualization julia_fractal_visualization(engine, julia_fractal, &camera_julia);
		engine.RegisterSystem(julia_fractal_visualization);
		engine.StartEngine();
	}
	{
		std::vector<stuff::CameraParameters> cameraParameters_mandelbrot = {
			stuff::CameraParameters{ 1.0, sf::Vector2d(-0.617745535714285, 0.0) }
		};
		stuff::Camera camera_mandelbrot = stuff::Camera(0.1, 1.0, 1.0, cameraParameters_mandelbrot);
		stuff::MandelbrotFractal mandelbrot_fractal = stuff::MandelbrotFractal(engine);
		stuff::FractalVisualization mandelbrot_fractal_visualization(engine, mandelbrot_fractal, &camera_mandelbrot);
		engine.RegisterSystem(mandelbrot_fractal_visualization);
		engine.StartEngine();
	}
	//{
	//	std::vector<stuff::CameraParameters> cameraParameters_mandelbrot = {
	//		stuff::CameraParameters{ 3.0, sf::Vector2d(-0.617745535714285, 0.0) },
	//		stuff::CameraParameters{ 0.0001, sf::Vector2d(-1.484474398577964, 0.0) }
	//	};
	//	stuff::Camera camera_mandelbrot = stuff::Camera(0.1, 3.0, 0.000291894716271, cameraParameters_mandelbrot);
	//	stuff::MandelbrotFractal mandelbrot_fractal = stuff::MandelbrotFractal(engine);
	//	stuff::FractalVisualization mandelbrot_fractal_visualization(engine, mandelbrot_fractal, &camera_mandelbrot);
	//	engine.RegisterSystem(mandelbrot_fractal_visualization);
	//	engine.StartEngine();
	//}
	//{
	//	std::vector<stuff::CameraParameters> cameraParameters_mandelbrot = {
	//		stuff::CameraParameters{ 3.0, sf::Vector2d(-0.617745535714285, 0.0) },
	//		stuff::CameraParameters{ 0.000309483601494, sf::Vector2d(-0.129405725859183, -1.020095244855847) },
	//		stuff::CameraParameters{ 0.000000029099614, sf::Vector2d(-0.129289541311080, -1.020059580908733) }
	//	};
	//	stuff::Camera camera_mandelbrot = stuff::Camera(0.15, 3.0, 0.000000000004896, cameraParameters_mandelbrot);
	//	stuff::MandelbrotFractal mandelbrot_fractal = stuff::MandelbrotFractal(engine);
	//	stuff::FractalVisualization mandelbrot_fractal_visualization(engine, mandelbrot_fractal, &camera_mandelbrot);
	//	engine.RegisterSystem(mandelbrot_fractal_visualization);
	//	engine.StartEngine();
	//}
	//{
	//	std::vector<stuff::CameraParameters> cameraParameters_mandelbrot = {
	//		stuff::CameraParameters{ 3.0, sf::Vector2d(-0.617745535714285, 0.0) },
	//		stuff::CameraParameters{ 0.000000017971462, sf::Vector2d(0.349358185500074, -0.512096616213581) }
	//	};
	//	stuff::Camera camera_mandelbrot = stuff::Camera(0.15, 3.0, 0.000000017971462, cameraParameters_mandelbrot);
	//	stuff::MandelbrotFractal mandelbrot_fractal = stuff::MandelbrotFractal(engine);
	//	stuff::FractalVisualization mandelbrot_fractal_visualization(engine, mandelbrot_fractal, &camera_mandelbrot);
	//	engine.RegisterSystem(mandelbrot_fractal_visualization);
	//	engine.StartEngine();
	//}
	//{
	//	std::vector<stuff::CameraParameters> cameraParameters_mandelbrot = {
	//		stuff::CameraParameters{ 3.0, sf::Vector2d(-0.617745535714285, 0.0) },
	//		stuff::CameraParameters{ 0.000000000058540, sf::Vector2d(-1.263071079818568, -0.408857715059257) }
	//	};
	//	stuff::Camera camera_mandelbrot = stuff::Camera(0.15, 3.0, 0.000000000058540, cameraParameters_mandelbrot);
	//	stuff::MandelbrotFractal mandelbrot_fractal = stuff::MandelbrotFractal(engine);
	//	stuff::FractalVisualization mandelbrot_fractal_visualization(engine, mandelbrot_fractal, &camera_mandelbrot);
	//	engine.RegisterSystem(mandelbrot_fractal_visualization);
	//	engine.StartEngine();
	//}
	//{
	//	std::vector<stuff::CameraParameters> cameraParameters_newton = {
	//		stuff::CameraParameters{ 1.0, sf::Vector2d(0.0, 0.0) },
	//		stuff::CameraParameters{ 0.0001, sf::Vector2d(-0.100634417106839, -0.266962857768278) }
	//	};
	//	stuff::Camera camera_newton = stuff::Camera(0.1, 5.0, 0.000119529129757, cameraParameters_newton);
	//	stuff::NewtonFractal newton_fractal = stuff::NewtonFractal(engine);
	//	stuff::FractalVisualization newton_ractal_visualization(engine, newton_fractal, &camera_newton);
	//	engine.RegisterSystem(newton_ractal_visualization);
	//	engine.StartEngine();
	//}
    return 0;
}
