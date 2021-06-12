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

//https://www.cs.technion.ac.il/users/yechiel/c++-faq/separate-template-class-defn-from-decl.html
// Cpp create to link definition of template class to declaration
namespace stuff::algo
{

template class BubbleSort<int>;
template class BubbleSort<float>;

template class QuickSort<int>;
template class QuickSort<float>;

template class CombSort<int>;
template class CombSort<float>;

template class CocktailSort<int>;
template class CocktailSort<float>;

template class MergeSort<int>;
template class MergeSort<float>;

template class GnomeSort<int>;
template class GnomeSort<float>;

template class OddEvenSort<int>;
template class OddEvenSort<float>;

template class HeapSort<int>;
template class HeapSort<float>;

template class InsertionSort<int>;
template class InsertionSort<float>;

template class StoogeSort<int>;
template class StoogeSort<float>;

template class SelectionSort<int>;
template class SelectionSort<float>;
}