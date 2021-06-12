#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <array>

void DisplaySize(int size, const std::string& name)
{
    std::cout << name << " : " << std::to_string(size) << std::endl;
}

TEST(SizeOf, Basic)
{
	char char_ = 0;
	int int_ = 0;
	float float_ = 0;
	double double_ = 0;
	size_t size_t_ = 0;
	char* char_ptr = nullptr;
	DisplaySize(sizeof(char_), "char_");
	DisplaySize(sizeof(int_), "int_");
	DisplaySize(sizeof(float_), "float_");
	DisplaySize(sizeof(double_), "double_");
	DisplaySize(sizeof(size_t_), "size_t_");
	DisplaySize(sizeof(char_ptr), "char_ptr");
	
}


TEST(SizeOf, Vec)
{
	std::string empty_string;
	std::string full_string = "abcdefghijklmnoprstuvwxyz";
	std::vector<char> empty_char_vec;
	std::vector<char> full_char_vec = std::vector<char>(100, 1);
	std::vector<float> empty_float_vec;
	std::vector<float> full_float_vec = std::vector<float>(100, 1);
	std::array<char, 1> empty_char_arr;
	std::array<char, 100> full_char_arr;
	std::array<float, 1> empty_float_arr;
	std::array<float, 100> full_float_arr;
	std::list<char> empty_char_list;
	std::list<char> full_char_list = std::list<char>(100, 1);
	std::list<float> empty_float_list;
	std::list<float> full_float_list = std::list<float>(100, 1);
	DisplaySize(sizeof(empty_string), "empty_string");
	DisplaySize(sizeof(full_string), "full_string");
	DisplaySize(sizeof(empty_char_vec), "empty_char_vec");
	DisplaySize(sizeof(full_char_vec), "full_char_vec");
	DisplaySize(sizeof(empty_float_vec), "empty_float_vec");
	DisplaySize(sizeof(full_float_vec), "full_float_vec");
	DisplaySize(sizeof(empty_char_arr), "empty_char_arr");
	DisplaySize(sizeof(full_char_arr), "full_char_arr");
	DisplaySize(sizeof(empty_float_arr), "empty_float_arr");
	DisplaySize(sizeof(full_float_arr), "full_float_arr");
	DisplaySize(sizeof(empty_char_list), "empty_char_list");
	DisplaySize(sizeof(full_char_list), "full_char_list");
	DisplaySize(sizeof(empty_float_list), "empty_float_list");
	DisplaySize(sizeof(full_float_list), "full_float_list");

}


struct Foo {
	char  char1_;
	double   double_;
	char  char2_;
	double   double2_;
	int  int_;
};

struct alignas(16) Foo2 {
	char  char1_;
	double   double_;
	char  char2_;
	double   double2_;
	int  int_;
};

struct Foo3 {
	double   double_;
	double   double2_;
	int  int_;
	char  char1_;
	char  char2_;
};

TEST(SizeOf, Class)
{
	Foo class_unaligned;
	DisplaySize(alignof(Foo), "Alignof(class_unaligned)");
	DisplaySize(sizeof(class_unaligned.double_) + sizeof(class_unaligned.double2_) + sizeof(class_unaligned.int_) + sizeof(class_unaligned.char1_) + sizeof(class_unaligned.char2_), "class_unaligned Sum");
	DisplaySize(sizeof(class_unaligned), "class_unaligned");
	Foo2 class_aligned_16;
	DisplaySize(alignof(Foo2), "Alignof(class_aligned_16)");
	DisplaySize(sizeof(class_aligned_16.double_) + sizeof(class_aligned_16.double2_) + sizeof(class_aligned_16.int_) + sizeof(class_aligned_16.char1_) + sizeof(class_aligned_16.char2_), "class_aligned_16 Sum");
	DisplaySize(sizeof(class_aligned_16), "class_aligned_16");
	Foo3 class_oraginized;
	DisplaySize(alignof(Foo3), "Alignof(class_oraginized)");
	DisplaySize(sizeof(class_oraginized.double_) + sizeof(class_oraginized.double2_) + sizeof(class_oraginized.int_) + sizeof(class_oraginized.char1_) + sizeof(class_oraginized.char2_), "class_oraginized Sum");
	DisplaySize(sizeof(class_oraginized), "class_oraginized");
}

struct Foo4 {
	std::vector<char> vec = std::vector<char>(500);
};

struct Foo5 {
	std::array<char, 31> vec;
	double double_;
};

struct Foo6 {
	double double_;
	std::array<char, 31> vec;
};

TEST(SizeOf, ClassVec)
{
	
	DisplaySize(alignof(std::array<char, 100>), "Alignof(std::array<char, 100>)");
	Foo4 class_vec;
	DisplaySize(alignof(Foo4), "Alignof(class_vec)");
	DisplaySize(sizeof(class_vec), "class_vec");
	Foo4* class_vec_ptr = new Foo4();
	DisplaySize(sizeof(*class_vec_ptr), "class_vec_ptr");
	Foo5 class_array;
	DisplaySize(alignof(Foo5), "Alignof(class_array)");
	DisplaySize(sizeof(class_array), "class_array");
	Foo6 class_array_align;
	DisplaySize(alignof(Foo6), "Alignof(class_array_align)");
	DisplaySize(sizeof(class_array_align), "class_array");
}
TEST(SizeOf, SmartPtr)
{
	std::unique_ptr<char> char_uptr = nullptr;
	std::unique_ptr<float> float_uptr = nullptr;
	std::shared_ptr<char> char_sptr = nullptr;
	std::shared_ptr<float> float_sptr = nullptr;
	std::weak_ptr<char> char_wptr;
	std::weak_ptr<float> float_wptr;
	DisplaySize(sizeof(char_uptr), "char_uptr");
	DisplaySize(sizeof(float_uptr), "float_uptr");
	DisplaySize(sizeof(char_sptr), "char_sptr");
	DisplaySize(sizeof(float_sptr), "float_sptr");
	DisplaySize(sizeof(char_wptr), "char_wptr");
	DisplaySize(sizeof(float_wptr), "float_wptr");

}