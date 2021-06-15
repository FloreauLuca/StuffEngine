#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"

//https://necessarydisorder.wordpress.com/2017/11/15/drawing-from-noise-and-then-making-animated-loopy-gifs-from-there/

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 900, 900 });
	engine.StartEngine();
    return 0;
}
