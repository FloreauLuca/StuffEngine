#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "music_noise.h"
#include "recursive_music.h"
#include "engine/engine.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	//engine.GetGraphics().SetWindowSize({ 900, 900 });
	engine.GetGraphics().SetWindowSize({ 450, 800 });
	//engine.GetGraphics().SetWindowSize({ 560, 1000 });
	//engine.GetGraphics().SetWindowSize({ 750, 750 });
	stuff::RecursiveMusic recursive_music(engine);
	engine.RegisterSystem(recursive_music);
	engine.StartEngine();
	stuff::MusicNoise music_noise(engine);
	engine.RegisterSystem(music_noise);
	engine.StartEngine();
    return 0;
}