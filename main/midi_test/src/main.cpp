#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "midi_reader.h"
#include "virtual_piano.h"
#include "engine/engine.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 450, 800 });
	stuff::VirtualPiano recursive_music(engine);
	//recursive_music.Init();
	//recursive_music.Update(0.16);
	engine.RegisterSystem(recursive_music);
	engine.StartEngine();
	return 0;
}