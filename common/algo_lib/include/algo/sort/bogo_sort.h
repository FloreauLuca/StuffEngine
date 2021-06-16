#pragma once
#include "sort.h"

//https://www.geeksforgeeks.org/bogosort-permutation-sort/

namespace stuff::algo
{
	template <Sortable T>
	class BogoSort final : public Sort<T>
	{
	public:
		using Sort<T>::SetList;
		std::vector<std::pair<size_t, size_t>> SortList();
	private :
		bool IsSorted();
		void Shuffle();
	};
}
