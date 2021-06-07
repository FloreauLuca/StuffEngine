#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <array>

#include "stack_heap_test.h"

class BasicClass {
public:
    int attribut;
};

int GLOBAL_INT = 10;
static int static_int = 10;
const int CONST_INT = 10;
static const int static_const_int = 10;
constexpr  int CONSTEXPR_INT = 10;
static constexpr int static_constexpr_int = 10;

void basic(int parameter) {
    BasicClass basic_class;
    BasicClass* class_ptr = new BasicClass();
    DisplayAddr(&parameter, "&parameter", Location::STACK);
    DisplayAddr(&basic_class, "&basic_class", Location::STACK);
    DisplayAddr(&basic_class.attribut, "&basic_class.attribut", Location::STACK);
    DisplayAddr(class_ptr, "class_ptr", Location::HEAP);
    DisplayAddr(&class_ptr, "&class_ptr", Location::STACK);
    DisplayAddr(&class_ptr->attribut, "&class_ptr->attribut", Location::HEAP);
	
    DisplayAddr(&GLOBAL_INT, "&GLOBAL_INT", Location::STATIC);
    DisplayAddr(&static_int, "&static_int", Location::STATIC);
    DisplayAddr(&CONST_INT, "&CONST_INT", Location::STATIC);
    DisplayAddr(&static_const_int, "&static_const_int", Location::STATIC);
    DisplayAddr(&CONSTEXPR_INT, "&CONSTEXPR_INT", Location::STATIC);
    DisplayAddr(&static_constexpr_int, "&static_constexpr_int", Location::STATIC);
}


TEST(StackHeap, Basic)
{
    InitMemSlot();
    basic(10);
}

void vector(std::vector<char> vec_param)
{
    char* char_vec_param = &vec_param[0];
    std::string string = "Vec";
    char* char_string = &string[0];
    std::vector<char> vec = { 0, 1, 2 };
    char* char_vec = &vec[2];
    std::array<char, 3> arr = { 0, 1, 2 };
    char* char_arr = &arr[2];

    DisplayAddr(&vec_param, "&vec_param", Location::STACK);
    DisplayAddr(char_vec_param, "char_vec_param", Location::HEAP);
    DisplayAddr(&string, "&string", Location::STACK);
    DisplayAddr(char_string, "char_string", Location::STACK);
    DisplayAddr(&vec, "&vec", Location::STACK);
    DisplayAddr(char_vec, "char_vec", Location::HEAP);
    DisplayAddr(&arr, "&arr", Location::STACK);
    DisplayAddr(char_arr, "char_arr", Location::STACK);
}

TEST(StackHeap, Vector)
{
    InitMemSlot();
    vector({ 0, 1 });
}