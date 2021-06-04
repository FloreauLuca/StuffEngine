#include <iostream>
#include <random>
#include <benchmark/benchmark.h>
#include "bubble_sort.h"
#include "quick_sort.h"
#include "merge_sort.h"
#include "cocktail_sort.h"
#include "comb_sort.h"

const unsigned long fromRange = 2;
const unsigned long toRange = 1 << 8;

static void BM_Algo_BubbleSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::BubbleSort bubble_sort;
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
	stuff::algo::QuickSort quick_sort;
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
	stuff::algo::CombSort comb_sort;
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
	stuff::algo::CocktailSort cocktail_sort;
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
	stuff::algo::MergeSort merge_sort;
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

// Run the benchmark
BENCHMARK_MAIN();