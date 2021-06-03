#include <iostream>
#include <random>
#include <benchmark/benchmark.h>
#include "bubble_sort.h"

const unsigned long fromRange = 2;
const unsigned long toRange = 1 << 10;

static void BM_Algo_BubbleSort(benchmark::State& state) {
	std::vector<int> list_;
	stuff::algo::BubbleSort bubble_sort_;
	const unsigned int listSize = state.range(0);
	for (int i = 0; i < listSize; ++i)
	{
		list_.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(list_.begin(), list_.end(), g);
	bubble_sort_.SetList(list_);
    // Perform setup here
    for (auto _ : state) {
		bubble_sort_.AutoSort();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_Algo_BubbleSort)->Range(fromRange, toRange);
// Run the benchmark
BENCHMARK_MAIN();