#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/engine.h"
#include "sfml_test.h"

int main()
{
	std::cout << "Salut" << std::endl;
	stuff::Engine engine;
	stuff::SfmlTest sfml_test(engine);
	engine.RegisterSystem(sfml_test);
	engine.StartEngine();
	engine.RegisterSystem(sfml_test);
	engine.StartEngine();
    return 0;
}
