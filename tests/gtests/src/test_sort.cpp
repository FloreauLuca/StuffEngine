
#include "gtest/gtest.h"

#include "sort_test.h"

#include "algo/sort/bubble_sort.h"
#include "algo/sort/quick_sort.h"
#include "algo/sort/merge_sort.h"
#include "algo/sort/cocktail_sort.h"
#include "algo/sort/comb_sort.h"

constexpr size_t LIST_SIZE = 100;

TEST(Algo, BubbleSort)
{
	stuff::algo::BubbleSort bubble_sort;
	bubble_sort.SetList(generateRandomList(LIST_SIZE));
	bubble_sort.SortList();
	EXPECT_TRUE(isSorted(bubble_sort.GetList()));
}


TEST(Algo, QuickSort)
{
	stuff::algo::QuickSort quick_sort;
	quick_sort.SetList(generateRandomList(LIST_SIZE));
	quick_sort.SortList();
	EXPECT_TRUE(isSorted(quick_sort.GetList()));
}


TEST(Algo, MergeSort)
{
	stuff::algo::MergeSort merge_sort;
	merge_sort.SetList(generateRandomList(LIST_SIZE));
	merge_sort.SortList();
	EXPECT_TRUE(isSorted(merge_sort.GetList()));
}


TEST(Algo, CombSort)
{
	stuff::algo::CombSort comb_sort;
	comb_sort.SetList(generateRandomList(LIST_SIZE));
	comb_sort.SortList();
	EXPECT_TRUE(isSorted(comb_sort.GetList()));
}

TEST(Algo, CocktailSort)
{
	stuff::algo::CocktailSort cocktail_sort;
	cocktail_sort.SetList(generateRandomList(LIST_SIZE));
	cocktail_sort.SortList();
	EXPECT_TRUE(isSorted(cocktail_sort.GetList()));
}