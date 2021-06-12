#include <iostream>
#include <random>
#include <benchmark/benchmark.h>
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

const unsigned long fromRange = 2;
const unsigned long toRange = 1 << 8;

static void BM_Algo_BubbleSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::BubbleSort<int> bubble_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	bubble_sort.SetList(list_);
    // Perform setup here
    for (auto _ : state) {
		bubble_sort.SortList();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_BubbleSort)->Range(fromRange, toRange);

static void BM_Algo_QuickSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::QuickSort<int> quick_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	quick_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		quick_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_QuickSort)->Range(fromRange, toRange);

static void BM_Algo_CombSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::CombSort<int> comb_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	comb_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		comb_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_CombSort)->Range(fromRange, toRange);

static void BM_Algo_CocktailSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::CocktailSort<int> cocktail_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	cocktail_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		cocktail_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_CocktailSort)->Range(fromRange, toRange);

static void BM_Algo_MergeSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::MergeSort<int> merge_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	merge_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		merge_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_MergeSort)->Range(fromRange, toRange);

static void BM_Algo_GnomeSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::GnomeSort<int> gnome_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	gnome_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		gnome_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_GnomeSort)->Range(fromRange, toRange);

static void BM_Algo_HeapSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::HeapSort<int> heap_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	heap_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		heap_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_HeapSort)->Range(fromRange, toRange);

static void BM_Algo_InsertionSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::InsertionSort<int> insertion_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	insertion_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		insertion_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_InsertionSort)->Range(fromRange, toRange);

static void BM_Algo_OddEvenSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::OddEvenSort<int> odd_even_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	odd_even_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		odd_even_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_OddEvenSort)->Range(fromRange, toRange);

static void BM_Algo_SelectionSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::SelectionSort<int> selection_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	selection_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		selection_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_SelectionSort)->Range(fromRange, toRange);

static void BM_Algo_StoogeSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::StoogeSort<int> stooge_sort;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	stooge_sort.SetList(list_);
	// Perform setup here
	for (auto _ : state) {
		stooge_sort.SortList();
	}
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_StoogeSort)->Range(fromRange, toRange);

// Run the benchmark
BENCHMARK_MAIN();