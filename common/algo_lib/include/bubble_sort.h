#pragma once
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff::algo
{

class BubbleSort
{
public:
	BubbleSort() = default;

	void SetList(const std::vector<int>& list);
	std::vector<int> GetList()const;
	std::pair<size_t, size_t> Update();
	void AutoSort();
	bool IsSorted() const { return sorted_; }
private:
	std::vector<int> list_;
	bool autoSort_ = true;
	bool sorted_ = false;
	size_t i_ = 0;
	size_t j_ = 0;
	size_t listSize_;
};
}

