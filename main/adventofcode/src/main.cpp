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
#include "day8_display.h"
#include "day9_smoke.h"
#include "day10_syntax.h"
#include "day11_octopus.h"
#include "day14_polymerization.h"
#include "day17_shot.h"
#include "day18_snailfish.h"
#include "day19_scanner.h"
#include "day20_trench.h"
#include "day21_dice.h"
#include "day22_cuboid.h"
#include "day13_origami.h"
#include "y2022_day9.h"


int main()
{
	stuff::Engine engine;
	engine.GetGraphics().SetWindowSize({ 500, 800 });
	stuff::advent::Day9 day(engine);
	day.ReadFromName("y2022_day9_test");
	//std::cout << day.FindAnswer();
	engine.RegisterSystem(day);
	engine.StartEngine();
	return 0;
}
