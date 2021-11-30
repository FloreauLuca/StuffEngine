#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <utility/data_location.h>
#include <fstream>
#include <string>

#include "day1_test.h"
#include "day2_test.h"

int main()
	{
		stuff::Engine engine;
		engine.GetGraphics().SetWindowSize({ 600, 600 });
		stuff::advent::Day2Test day1(engine);
		day1.ReadFromName("test");
		std::cout << day1.FindAnswer();
		return 0;
	}
