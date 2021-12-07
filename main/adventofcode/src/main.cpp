#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <utility/data_location.h>
#include <fstream>
#include <string>

#include "day1_submarine.h"
#include "day2_movement.h"
#include "day3_binary.h"
#include "day4_bingo.h"
#include "day5_vents.h"
#include "day6_lanternfish.h"
#include "day7_whale.h"

int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 600, 600 });
	stuff::advent::Day7Whale day(engine);
	day.ReadFromName("day7_1");
	std::cout << day.FindAnswer();
	return 0;
}
