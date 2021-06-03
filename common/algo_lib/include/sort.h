#pragma once
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff::algo
{
class Sort
{
public:
	Sort() = default;

	virtual std::vector<std::pair<size_t, size_t>> SortList() = 0;
	
	void SetList(const std::vector<int>& list);
	std::vector<int> GetList() const { return list_; }
	bool IsSorted() const { return sorted_; }
protected:
	std::vector<int> list_;
	bool autoSort_ = true;
	bool sorted_ = false;
	size_t listSize_;
};
}
