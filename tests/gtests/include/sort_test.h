#include <random>
#include <vector>
#include "algo/sort/sort.h"

template<stuff::algo::Sortable T>
bool isSorted(const std::vector<T>& list)
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

template<typename T> requires std::is_arithmetic<T>::value
std::vector<T> generateRandomList(const size_t listSize)
{

	std::vector<T> list;
	for (int i = 0; i < listSize; ++i)
	{
		list.push_back(T(i));
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list.begin(), list.end(), g);
	return list;
}

template<stuff::algo::Sortable T>
std::vector<T> randomList(std::vector<T>& list)
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list.begin(), list.end(), g);
	return list;
}