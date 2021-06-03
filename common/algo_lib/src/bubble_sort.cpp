#include "bubble_sort.h"

namespace stuff::algo
{
void BubbleSort::SetList(const std::vector<int>& list)
{
	list_ = list;
	listSize_ = list_.size();
}

std::vector<int> BubbleSort::GetList() const
{
	return list_;
}

std::pair<size_t, size_t> BubbleSort::Update()
{
	std::pair<size_t, size_t> returnPair(0, 0);
	if (sorted_) return returnPair;
	if (j_ < listSize_ - i_ - 1)
	{
		if (list_[j_] > list_[j_ + 1])
		{
			returnPair = std::pair<size_t, size_t>(j_, j_ + 1);
			std::swap(list_[j_], list_[j_ + 1]);
		}
		j_++;
		return returnPair;
	}
	if (i_ < list_.size() - 1)
	{
		i_++;
		j_ = 0;
		return returnPair;
	}
	sorted_ = true;
	return returnPair;
}

void BubbleSort::AutoSort()
{
	int i, j;
	bool swapped;
	for (i = 0; i < listSize_ - 1; i++)
	{
		swapped = false;
		for (j = 0; j < listSize_ - i - 1; j++)
		{
			if (list_[j] > list_[j + 1])
			{
				std::swap(list_[j], list_[j + 1]);
				swapped = true;
			}
		}

		// IF no two elements were swapped by inner loop, then break
		if (swapped == false)
			break;
	}
}
}
