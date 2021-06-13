#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "image_drawing.h"
#include "engine/engine.h"
#include "sfml_test.h"
#include "mouse_simulation.h"
#include "sound_test.h"
#include "vertex_array_drawing.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	stuff::VertexArrayDrawing vertex_array_drawing(engine);
	engine.RegisterSystem(vertex_array_drawing);
	engine.StartEngine();
	stuff::ImageDrawing image_drawing(engine);
	engine.RegisterSystem(image_drawing);
	engine.StartEngine();
	stuff::MouseSim mouse_sim(engine);
	engine.RegisterSystem(mouse_sim);
	engine.StartEngine();
	stuff::SoundTest sound_test(engine);
	engine.RegisterSystem(sound_test);
	engine.StartEngine();
	stuff::SfmlTest sfml_test(engine);
	engine.RegisterSystem(sfml_test);
	engine.StartEngine();
    return 0;
}
