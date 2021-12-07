#include <day.h>

#include <assert.h>
#include <sstream>

namespace stuff::advent
{
	void Day::Init()
	{
	}

	void Day::Update(float dt)
	{
	}

	void Day::Destroy()
	{
	}

	void Day::Read(std::string path)
	{
		myFile_.open(path);
		assert(myFile_.is_open(), "File not found");
	}

	void Day::ReadFromName(std::string name)
	{
		Read(stuff::dataPath + "adventofcode/" + name + ".txt");
	}

	std::string Day::FindAnswer()
	{
		return "";
	}

	void Day::DisplayAnswer()
	{

	}

	void Day::ParseInt()
	{
		intParsing_ = std::vector<int>();
		while (!myFile_.eof())
		{
			int value;
			myFile_ >> value;
			intParsing_.push_back(value);
		}
	}

	void Day::ParseLineInt()
	{
		char between = ',';
		std::string entry = " ";
		std::getline(myFile_, entry);
		std::stringstream entrystream(entry);
		while (!entrystream.eof())
		{
			int value;
			entrystream >> value;
			intParsing_.push_back(value);
			entrystream >> between;
		}
	}

	void Day::ParseString()
	{
		stringParsing_ = std::vector<std::string>();
		while (!myFile_.eof())
		{
			std::string value;
			myFile_ >> value;
			stringParsing_.push_back(value);
		}
	}
}



