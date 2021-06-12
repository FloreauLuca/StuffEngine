#include "algo/sort/cocktail_sort.h"

namespace stuff::algo
{
    template<class T>
std::vector<std::pair<size_t, size_t>> CocktailSort<T>::SortList()
{
    bool swapped = true;
    int start = 0;
    int end = this->listSize_ - 1;

    while (swapped)
    {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;

        // loop from left to right same as
        // the bubble sort
        for (size_t i = start; i < end; ++i)
        {
            if (this->list_[i] > this->list_[i + 1]) {
	            std::swap(this->list_[i], this->list_[i + 1]);
                this->swapList_.push_back(std::pair<size_t, size_t>(i, i + 1));
                this->coloredList_.push_back(std::vector<size_t>{i, i + 1});
                swapped = true;
            }
        }

        // if nothing moved, then array is sorted.
        if (!swapped)
            break;

        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;

        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;

        // from right to left, doing the
        // same comparison as in the previous stage
        for (size_t i = end; i > start; --i)
        {
            if (this->list_[i-1] > this->list_[i]) {
	            std::swap(this->list_[i-1], this->list_[i]);
                this->swapList_.push_back(std::pair<size_t, size_t>(i-1, i));
                this->coloredList_.push_back(std::vector<size_t>{i-1, i});
                swapped = true;
            }
        }

        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
    return this->swapList_;
}
}
