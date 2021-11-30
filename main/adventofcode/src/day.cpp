#include <day.h>

#include <assert.h>

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
		myFile.open(path);
		assert(myFile.is_open(), "File not found");
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

}



