#include <day2_test.h>

namespace stuff::advent
{
	std::string Day2Test::FindAnswer()
	{
		std::string myString;
		while (!myFile.eof()) {
			std::string line;
			std::getline(myFile, line);
			myString += line;
			myString += '\n';
		}
		return myString;
	}

	void Day2Test::DisplayAnswer()
	{

	}
}

