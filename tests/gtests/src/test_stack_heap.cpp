#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>
void* first_stack = nullptr;
void* first_heap = nullptr;
void* first_static = nullptr;

constexpr size_t MEM_SIZE = 1 << 24;
enum class Location
{
    UNKNOW,
	STATIC,
	STACK,
	HEAP
};

std::string memSlot(const void* addr)
{
	if (abs(static_cast<long long>(reinterpret_cast<size_t>(first_heap)) - static_cast<long long>(reinterpret_cast<size_t>(addr))) < MEM_SIZE)
	{
        return "Heap";
	}
    if (abs(static_cast<long long>(reinterpret_cast<size_t>(first_stack)) - static_cast<long long>(reinterpret_cast<size_t>(addr))) < MEM_SIZE)
    {
        return "Stack";
    }
    if (abs(static_cast<long long>(reinterpret_cast<size_t>(first_static)) - static_cast<long long>(reinterpret_cast<size_t>(addr))) < MEM_SIZE)
    {
        return "Static";
    }
	return "Unknow";
}

void DisplayAddr(const void* addr, const std::string& name, Location location)
{
    std::cout << addr << " , " << name << " : " << memSlot(addr) << std::endl;
    switch (location) {
    case Location::STATIC:
	    {
			EXPECT_NEAR((size_t)addr, (size_t)first_static, MEM_SIZE);
	    }
    	break;
    case Location::STACK:
	    {
			EXPECT_NEAR((size_t)addr, (size_t)first_stack, MEM_SIZE);
	    }
    	break;
    case Location::HEAP:
	    {
			EXPECT_NEAR((size_t)addr, (size_t)first_heap, MEM_SIZE);
	    }
    	break;
    default: ;
    }
}

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

void vector(std::vector<char> vec_param)
{
    char* char_vec_param = &vec_param[0];
    std::string string = "Vec";
    char* char_string = &string[0];
    std::vector<char> vec = { 0, 1, 2};
    char* char_vec = &vec[2];
    std::vector<char*> vec_ptr = { new char(0) };
    char* char_vec_ptr = vec_ptr[0];
    std::array<char, 3> arr = { 0, 1, 2 };
    char* char_arr = &arr[2];
    std::array<char*, 1> arr_ptr = { new char(0) };
    char* char_arr_ptr = arr_ptr[0];

    DisplayAddr(&vec_param, "&vec_param", Location::UNKNOW);
    DisplayAddr(char_vec_param, "char_vec_param", Location::UNKNOW);
    DisplayAddr(&string, "&string", Location::UNKNOW);
    DisplayAddr(char_string, "char_string", Location::UNKNOW);
    DisplayAddr(&vec, "&vec", Location::UNKNOW);
    DisplayAddr(char_vec, "char_vec", Location::UNKNOW);
    DisplayAddr(&vec_ptr, "&vec_ptr", Location::UNKNOW);
    DisplayAddr(char_vec_ptr, "char_vec_ptr", Location::UNKNOW);
    DisplayAddr(&arr, "&arr", Location::UNKNOW);
    DisplayAddr(char_arr, "char_arr", Location::UNKNOW);
    DisplayAddr(&arr_ptr, "&arr_ptr", Location::UNKNOW);
    DisplayAddr(char_arr_ptr, "char_arr_ptr", Location::UNKNOW);
}

TEST(Keyword, StackHeap)
{
	
    char stack = 0;
    char* heap = new char();
    static char static_ = 0;
    first_stack = &stack;
    first_heap = heap;
    first_static = &static_;
    DisplayAddr(&stack, "First Stack", Location::STACK);
    DisplayAddr(heap, "First heap", Location::HEAP);
    DisplayAddr(&static_, "First Static", Location::STATIC);
    basic(10);
    vector({ 0, 1 });
}