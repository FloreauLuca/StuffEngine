#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	engine.StartEngine();
    return 0;
}
