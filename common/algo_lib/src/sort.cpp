#include "sort.h"

namespace stuff::algo
{

void Sort::SetList(const std::vector<int>& list)
{
	list_ = list;
	listSize_ = list_.size();
}
}