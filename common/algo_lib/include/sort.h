#pragma once
#include <concepts>
#include "engine/engine.h"
#include "engine/system.h"

namespace stuff::algo
{
template<class T>
concept Sortable = requires(T a) {
	std::totally_ordered<T>;
};

template<class T>
class Sort
{
public:
	Sort() = default;

	virtual std::vector<std::pair<size_t, size_t>> SortList() = 0;
	
	void SetList(const std::vector<T>& list);
	[[nodiscard]] std::vector<T> GetList() const { return list_; }
	[[nodiscard]] std::vector<std::vector<size_t>> GetColoredList() const { return coloredList_; }
	[[nodiscard]] bool IsSorted() const { return sorted_; }
protected:
	~Sort() = default;
	std::vector<T> list_;
	bool autoSort_ = true;
	bool sorted_ = false;
	size_t listSize_ = 0;
	std::vector<std::pair<size_t, size_t>> swapList_;
	std::vector<std::vector<size_t>> coloredList_;
};
}
