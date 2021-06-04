#include "comb_sort.h"

namespace stuff::algo
{
    int CombSort::GetNextGap(int gap)
    {
        // Shrink gap by Shrink factor
        gap = (gap * 10) / 13;

        if (gap < 1)
            return 1;
        return gap;
    }

std::vector<std::pair<size_t, size_t>> CombSort::SortList()
{
    // Initialize gap
    int gap = listSize_;

    // Initialize swapped as true to make sure that
    // loop runs
    bool swapped = true;

    // Keep running while gap is more than 1 and last
    // iteration caused a swap
    while (gap != 1 || swapped == true)
    {
        // Find next gap
        gap = GetNextGap(gap);

        // Initialize swapped as false so that we can
        // check if swap happened or not
        swapped = false;

        // Compare all elements with current gap
        for (size_t i = 0; i < listSize_ - gap; i++)
        {
            if (list_[i] > list_[i + gap])
            {
	            std::swap(list_[i], list_[i + gap]);
                swapList_.push_back(std::pair<size_t, size_t>(i, i + gap));
                coloredList_.push_back(std::vector<size_t>{i, i + gap});
                swapped = true;
            }
        }
    }
    return swapList_;
}
}
