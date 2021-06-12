#pragma once
#include "sort.h"
#include "engine/engine.h"

namespace stuff::algo
{
	template<class T>
class CocktailSort final : public Sort<T>
{
public:
	using Sort<T>::SetList;
	std::vector<std::pair<size_t, size_t>> SortList();
};
}
