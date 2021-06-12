#include <random>
#include <vector>

bool isSorted(const std::vector<int>& list)
{
	for (int i = 0; i < list.size() - 1; ++i)
	{
		if (list[i] > list[i + 1])
		{
			return false;
		}
	}
	return true;
}

std::vector<int> generateRandomList(const size_t listSize)
{

	std::vector<int> list;
	for (int i = 0; i < listSize; ++i)
	{
		list.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list.begin(), list.end(), g);
	return list;
}