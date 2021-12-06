#include <day2_movement.h>

namespace stuff::advent
{
	std::string Day2Movement::FindAnswer()
	{
		int horizontal = 0;
		int vertical = 0;
		int aim = 0;
		while (!myFile_.eof()) {
			std::string command = "";
			myFile_ >> command;
			int value;
			myFile_ >> value;
			
			if (command == "forward")
			{
				vertical += value;
				horizontal += aim * value;
			} else if (command == "down")
			{
				//horizontal += value;
				aim += value;
			} else
			{
				//horizontal -= value;
				aim -= value;
			}
		}
		return std::to_string((horizontal * vertical));
	}

	void Day2Movement::DisplayAnswer()
	{

	}
}

