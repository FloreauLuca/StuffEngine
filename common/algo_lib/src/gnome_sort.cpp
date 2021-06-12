#pragma once
#include "algo/sort/gnome_sort.h"

namespace stuff::algo
{
	std::vector<std::pair<size_t, size_t>> GnomeSort::SortList()
	{

        int index = 0;

        while (index < listSize_) {
            if (index == 0)
                index++;
            if (list_[index] >= list_[index - 1])
                index++;
            else {
                std::swap(list_[index], list_[index - 1]);
                swapList_.push_back(std::pair<size_t, size_t>(index, index - 1));
                coloredList_.push_back(std::vector<size_t>{(unsigned)index, (unsigned)index - 1});
                index--;
            }
        }
        return swapList_;
	}
}
