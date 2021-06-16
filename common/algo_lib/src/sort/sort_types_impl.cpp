#include "bubble_sort.cpp"
#include "cocktail_sort.cpp"
#include "comb_sort.cpp"
#include "merge_sort.cpp"
#include "quick_sort.cpp"
#include "gnome_sort.cpp"
#include "odd_even_sort.cpp"
#include "selection_sort.cpp"
#include "stooge_sort.cpp"
#include "heap_sort.cpp"
#include "insertion_sort.cpp"
#include "bogo_sort.cpp"
#include "cycle_sort.cpp"
#include "pancake_sort.cpp"
#include "shell_sort.cpp"
#include "tim_sort.cpp"

//https://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-class-defn-from-decl.html
// Cpp create to link definition of template class to declaration
namespace stuff::algo
{

template class BubbleSort<char>;
template class BubbleSort<unsigned>;
template class BubbleSort<int>;
template class BubbleSort<float>;

template class QuickSort<char>;
template class QuickSort<unsigned>;
template class QuickSort<int>;
template class QuickSort<float>;

template class CombSort<char>;
template class CombSort<unsigned>;
template class CombSort<int>;
template class CombSort<float>;

template class CocktailSort<char>;
template class CocktailSort<unsigned>;
template class CocktailSort<int>;
template class CocktailSort<float>;

template class MergeSort<char>;
template class MergeSort<unsigned>;
template class MergeSort<int>;
template class MergeSort<float>;

template class GnomeSort<char>;
template class GnomeSort<unsigned>;
template class GnomeSort<int>;
template class GnomeSort<float>;

template class OddEvenSort<char>;
template class OddEvenSort<unsigned>;
template class OddEvenSort<int>;
template class OddEvenSort<float>;

template class HeapSort<char>;
template class HeapSort<unsigned>;
template class HeapSort<int>;
template class HeapSort<float>;

template class InsertionSort<char>;
template class InsertionSort<unsigned>;
template class InsertionSort<int>;
template class InsertionSort<float>;

template class StoogeSort<char>;
template class StoogeSort<unsigned>;
template class StoogeSort<int>;
template class StoogeSort<float>;

template class SelectionSort<char>;
template class SelectionSort<unsigned>;
template class SelectionSort<int>;
template class SelectionSort<float>;

template class BogoSort<char>;
template class BogoSort<unsigned>;
template class BogoSort<int>;
template class BogoSort<float>;

template class CycleSort<char>;
template class CycleSort<unsigned>;
template class CycleSort<int>;
template class CycleSort<float>;

template class PancakeSort<char>;
template class PancakeSort<unsigned>;
template class PancakeSort<int>;
template class PancakeSort<float>;

template class ShellSort<char>;
template class ShellSort<unsigned>;
template class ShellSort<int>;
template class ShellSort<float>;

template class TimSort<char>;
template class TimSort<unsigned>;
template class TimSort<int>;
template class TimSort<float>;
}