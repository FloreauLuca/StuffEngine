#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


#include "color_test.h"
#include "image_drawing.h"
#include "midi_test.h"
#include "engine/engine.h"
#include "sfml_test.h"
#include "mouse_simulation.h"
#include "music_test.h"
#include "sound_test.h"
#include "vertex_array_drawing.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	stuff::MidiTest midi_test(engine);
	engine.RegisterSystem(midi_test);
	engine.StartEngine();
	stuff::ColorTest color_test(engine);
	engine.RegisterSystem(color_test);
	engine.StartEngine();
	stuff::MusicTest music_test(engine);
	engine.RegisterSystem(music_test);
	engine.StartEngine();
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
