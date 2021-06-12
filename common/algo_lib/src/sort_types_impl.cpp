#include "bubble_sort.cpp"
#include "cocktail_sort.cpp"
#include "comb_sort.cpp"
#include "merge_sort.cpp"
#include "quick_sort.cpp"

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
}