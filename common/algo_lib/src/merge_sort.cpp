#include "algo/sort/merge_sort.h"

namespace stuff::algo
{
std::vector<std::pair<size_t, size_t>> MergeSort::SortList()
{
    MergeSortFunc(0, listSize_ - 1);
    return swapList_;
}
void MergeSort::Merge(int start, int mid, int end)
{

    int start2 = mid + 1;

    // If the direct merge is already sorted
    if (list_[mid] <= list_[start2]) {
        return;
    }

    // Two pointers to maintain start
    // of both arrays to merge
    while (start <= mid && start2 <= end) {

        // If element 1 is in right place
        if (list_[start] <= list_[start2]) {
            start++;
        }
        else {
            int value = list_[start2];
            size_t index = start2;
            int switchPos = start2;
            // Shift all the elements between element 1
            // element 2, right by 1.
            while (index != start) {
                list_[index] = list_[index - 1];
                swapList_.push_back(std::pair<size_t, size_t>(index, index - 1));
                coloredList_.push_back(std::vector<size_t>{index, index - 1});
            	if (index == start2)
            	{
                    switchPos = index - 1;
            	}
                if (index -1 == start2)
                {
                    switchPos = index;
                }
                index--;
            }
            list_[start] = value; // ?????
            //swapList_.push_back(std::pair<size_t, size_t>(start, switchPos));

            // Update all the pointers
            start++;
            mid++;
            start2++;
        }
    }
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void MergeSort::MergeSortFunc(int l, int r) {
    if (l >= r) {
        return;//returns recursively
    }
    int m = l + (r - l) / 2;
    MergeSortFunc(l, m);
    MergeSortFunc(m + 1, r);
    Merge(l, m, r);
}
}
