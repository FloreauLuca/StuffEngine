#include "sort.h"

namespace stuff::algo
{
template<class T>
void Sort<T>::SetList(const std::vector<T>& list)
{
	list_ = list;
	listSize_ = list_.size();
}
}