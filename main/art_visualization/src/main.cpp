#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "color_palette.h"
#include "fire_particles.h"
#include "rotating_line.h"
#include "point_wave.h"
#include "moving_stars.h"
#include "music_noise.h"
#include "snow_flakes.h"
#include "engine/engine.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	//engine.GetGraphics().SetWindowSize({ 900, 900 });
	engine.GetGraphics().SetWindowSize({ 450, 800 });
	//engine.GetGraphics().SetWindowSize({ 750, 750 });
	stuff::FireParticles fire_particles(engine);
	engine.RegisterSystem(fire_particles);
	engine.StartEngine();
	stuff::MusicNoise music_noise(engine);
	engine.RegisterSystem(music_noise);
	engine.StartEngine();
	stuff::SnowFlakes snow_flakes(engine);
	engine.RegisterSystem(snow_flakes);
	engine.StartEngine();
	stuff::MovingStars moving_stars(engine);
	engine.RegisterSystem(moving_stars);
	engine.StartEngine(); 
	stuff::PointWave point_wave(engine);
	engine.RegisterSystem(point_wave);
	engine.StartEngine();
	stuff::RotatingLine rotating_line(engine);
	engine.RegisterSystem(rotating_line);
	engine.StartEngine();
	stuff::ColorPalette color_palette(engine);
	engine.RegisterSystem(color_palette);
	engine.StartEngine();
    return 0;
}
