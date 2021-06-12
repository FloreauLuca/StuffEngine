#pragma once
#include "algo/sort/gnome_sort.h"

namespace stuff::algo
{
    template<class T>
	std::vector<std::pair<size_t, size_t>> GnomeSort<T>::SortList()
	{

        int index = 0;

        while (index < this->listSize_) {
            if (index == 0)
                index++;
            if (this->list_[index] >= this->list_[index - 1])
                index++;
            else {
                std::swap(this->list_[index], this->list_[index - 1]);
                this->swapList_.push_back(std::pair<size_t, size_t>(index, index - 1));
                this->coloredList_.push_back(std::vector<size_t>{(unsigned)index, (unsigned)index - 1});
                index--;
            }
        }
        return this->swapList_;
	}
}
