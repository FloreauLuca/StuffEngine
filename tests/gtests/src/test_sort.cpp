
#include "gtest/gtest.h"

#include <utility>

#include "sort_test.h"
#include <algo/sort/sort_types_impl.h>

#include "algo/sort/bubble_sort.h"
#include "algo/sort/quick_sort.h"
#include "algo/sort/merge_sort.h"
#include "algo/sort/cocktail_sort.h"
#include "algo/sort/comb_sort.h"
#include "algo/sort/gnome_sort.h"
#include "algo/sort/heap_sort.h"
#include "algo/sort/insertion_sort.h"
#include "algo/sort/odd_even_sort.h"
#include "algo/sort/selection_sort.h"
#include "algo/sort/stooge_sort.h"

constexpr size_t LIST_SIZE = 100;

TEST(AlgoSort, BubbleSort)
{
	stuff::algo::BubbleSort<int> bubble_sort;
	bubble_sort.SetList(generateRandomList<int>(LIST_SIZE));
	bubble_sort.SortList();
	EXPECT_TRUE(isSorted<int>(bubble_sort.GetList()));
}


TEST(AlgoSort, QuickSort)
{
	stuff::algo::QuickSort<int> quick_sort;
	quick_sort.SetList(generateRandomList<int>(LIST_SIZE));
	quick_sort.SortList();
	EXPECT_TRUE(isSorted<int>(quick_sort.GetList()));
}


TEST(AlgoSort, MergeSort)
{
	stuff::algo::MergeSort<int> merge_sort;
	merge_sort.SetList(generateRandomList<int>(LIST_SIZE));
	merge_sort.SortList();
	EXPECT_TRUE(isSorted<int>(merge_sort.GetList()));
}


TEST(AlgoSort, CombSort)
{
	stuff::algo::CombSort<int> comb_sort;
	comb_sort.SetList(generateRandomList<int>(LIST_SIZE));
	comb_sort.SortList();
	EXPECT_TRUE(isSorted<int>(comb_sort.GetList()));
}

TEST(AlgoSort, CocktailSort)
{
	stuff::algo::CocktailSort<int> cocktail_sort;
	cocktail_sort.SetList(generateRandomList<int>(LIST_SIZE));
	cocktail_sort.SortList();
	EXPECT_TRUE(isSorted<int>(cocktail_sort.GetList()));
}

TEST(AlgoSort, GnomeSort)
{
	stuff::algo::GnomeSort<int> gnome_sort;
	gnome_sort.SetList(generateRandomList<int>(LIST_SIZE));
	gnome_sort.SortList();
	EXPECT_TRUE(isSorted<int>(gnome_sort.GetList()));
}

TEST(AlgoSort, HeapSort)
{
	stuff::algo::HeapSort<int> heap_sort;
	heap_sort.SetList(generateRandomList<int>(LIST_SIZE));
	heap_sort.SortList();
	EXPECT_TRUE(isSorted<int>(heap_sort.GetList()));
}

TEST(AlgoSort, InsertionSort)
{
	stuff::algo::InsertionSort<int> insertion_sort;
	insertion_sort.SetList(generateRandomList<int>(LIST_SIZE));
	insertion_sort.SortList();
	EXPECT_TRUE(isSorted<int>(insertion_sort.GetList()));
}

TEST(AlgoSort, OddEvenSort)
{
	stuff::algo::OddEvenSort<int> odd_even_sort;
	odd_even_sort.SetList(generateRandomList<int>(LIST_SIZE));
	odd_even_sort.SortList();
	EXPECT_TRUE(isSorted<int>(odd_even_sort.GetList()));
}

TEST(AlgoSort, SelectionSort)
{
	stuff::algo::SelectionSort<int> selection_sort;
	selection_sort.SetList(generateRandomList<int>(LIST_SIZE));
	selection_sort.SortList();
	EXPECT_TRUE(isSorted<int>(selection_sort.GetList()));
}

TEST(AlgoSort, StoogeSort)
{
	stuff::algo::StoogeSort<int> stooge_sort;
	stooge_sort.SetList(generateRandomList<int>(LIST_SIZE));
	stooge_sort.SortList();
	EXPECT_TRUE(isSorted<int>(stooge_sort.GetList()));
}


struct A
{
	int i;
	auto operator<=>(const A& lhs) const
	{
		if (lhs.i < this->i) return 1;
		if (lhs.i > this->i) return -1;
		return 0;
	}
};


template class stuff::algo::BubbleSort<A>;

TEST(AlgoSort, BubbleSortClass)
{
	stuff::algo::BubbleSort<A> bubble_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{i});
	}
	list = randomList(list);
	bubble_sort.SetList(list);
	bubble_sort.SortList();
	list = bubble_sort.GetList();
	EXPECT_TRUE(isSorted<A>(list));
	//for (int i = 0; i < LIST_SIZE; ++i)
	//{
	//	std::cout << list[i].i << ", ";
	//}
	//std::cout << std::endl;
	
}

template class stuff::algo::QuickSort<A>;

TEST(AlgoSort, QuickSortClass)
{
	stuff::algo::QuickSort<A> quick_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	quick_sort.SetList(list);
	quick_sort.SortList();
	EXPECT_TRUE(isSorted<A>(quick_sort.GetList()));
}

template class stuff::algo::MergeSort<A>;

TEST(AlgoSort, MergeSortClass)
{
	stuff::algo::MergeSort<A> merge_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	merge_sort.SetList(list);
	merge_sort.SortList();
	EXPECT_TRUE(isSorted<A>(merge_sort.GetList()));
}

template class stuff::algo::CombSort<A>;

TEST(AlgoSort, CombSortClass)
{
	stuff::algo::CombSort<A> comb_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	comb_sort.SetList(list);
	comb_sort.SortList();
	EXPECT_TRUE(isSorted<A>(comb_sort.GetList()));
}

template class stuff::algo::CocktailSort<A>;

TEST(AlgoSort, CocktailSortClass)
{
	stuff::algo::CocktailSort<A> cocktail_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	cocktail_sort.SetList(list);
	cocktail_sort.SortList();
	EXPECT_TRUE(isSorted<A>(cocktail_sort.GetList()));
}

template class stuff::algo::GnomeSort<A>;

TEST(AlgoSort, GnomeSortClass)
{
	stuff::algo::GnomeSort<A> gnome_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	gnome_sort.SetList(list);
	gnome_sort.SortList();
	EXPECT_TRUE(isSorted<A>(gnome_sort.GetList()));
}

template class stuff::algo::HeapSort<A>;

TEST(AlgoSort, HeapSortClass)
{
	stuff::algo::HeapSort<A> heap_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	heap_sort.SetList(list);
	heap_sort.SortList();
	EXPECT_TRUE(isSorted<A>(heap_sort.GetList()));
}

template class stuff::algo::InsertionSort<A>;

TEST(AlgoSort, InsertionSortClass)
{
	stuff::algo::InsertionSort<A> insertion_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	insertion_sort.SetList(list);
	insertion_sort.SortList();
	EXPECT_TRUE(isSorted<A>(insertion_sort.GetList()));
}

template class stuff::algo::OddEvenSort<A>;

TEST(AlgoSort, OddEvenSortClass)
{
	stuff::algo::OddEvenSort<A> odd_even_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	odd_even_sort.SetList(list);
	odd_even_sort.SortList();
	EXPECT_TRUE(isSorted<A>(odd_even_sort.GetList()));
}

template class stuff::algo::SelectionSort<A>;

TEST(AlgoSort, SelectionSortClass)
{
	stuff::algo::SelectionSort<A> selection_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	selection_sort.SetList(list);
	selection_sort.SortList();
	EXPECT_TRUE(isSorted<A>(selection_sort.GetList()));
}

template class stuff::algo::StoogeSort<A>;

TEST(AlgoSort, StoogeSortClass)
{
	stuff::algo::StoogeSort<A> stooge_sort;
	std::vector<A> list;
	for (int i = 0; i < LIST_SIZE; ++i)
	{
		list.push_back(A{ i });
	}
	list = randomList(list);
	stooge_sort.SetList(list);
	stooge_sort.SortList();
	EXPECT_TRUE(isSorted<A>(stooge_sort.GetList()));
}