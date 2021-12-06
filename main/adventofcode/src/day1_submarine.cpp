#include <day1_submarine.h>

namespace stuff::advent
{
	std::string Day1Submarine::FindAnswer()
	{
		ParseInt();
		int count = 0;
		for (int i = 0; i < intParsing_.size() - 3; ++i)
		{
			//if (intParsing_[i] < intParsing_[i+1])
			//{
			//	count++;
			//}
			if (intParsing_[i] + intParsing_[i+1] + intParsing_[i+2] <
				intParsing_[i + 1] + intParsing_[i + 2] + intParsing_[i + 3])
			{
				count++;
			}
		}
		return std::to_string(count);
	}

	void Day1Submarine::DisplayAnswer()
	{

	}
}

