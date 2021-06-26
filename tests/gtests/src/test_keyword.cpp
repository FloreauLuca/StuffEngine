#include "gtest/gtest.h"

#include <array>
#include <vector>
#include <string>
#include <type_traits>
#include <iostream>

struct Foo {
    int   i;
    float f;
    char  c;
};

struct alignas(alignof(long double)) Foo2 {
    int   i;
    float f;
    char  c;
};

//l'alignement ne peut pas être défini sur une valeur inférieure à l'alignement par défaut
struct /*alignas(alignof(int))*/ Foo3 {
    std::array<int, 6> i;
    std::vector<float> f;
    std::string  c;
};

struct Empty {};

struct alignas(64) Empty64 {};

TEST(Keyword, Alignof)
{
    std::cout << "Alignment of"  "\n"
        "- char             : " << alignof(char) << "\n"
        "- int              : " << alignof(int) << "\n"
        "- float            : " << alignof(float) << "\n"
        "- double           : " << alignof(double) << "\n"
        "- size_t           : " << alignof(size_t) << "\n"
        "- pointer          : " << alignof(int*) << "\n"
        "- std::array<int, 6> : " << alignof(std::array<int, 6>) << "\n"
        "- std::vector<float> : " << alignof(std::vector<float>) << "\n"
        "- std::string      : " << alignof(std::string) << "\n"
        "- class Foo        : " << alignof(Foo) << "\n"
        "- class Foo2       : " << alignof(Foo2) << "\n"
        "- class Foo3       : " << alignof(Foo3) << "\n"
        "- empty class      : " << alignof(Empty) << "\n"
        "- alignas(64) Empty: " << alignof(Empty64) << "\n";
}

// every object of type struct_float will be aligned to alignof(float) boundary
// (usually 4)
struct alignas(float) struct_float {
    // your definition here
};

// every object of type sse_t will be aligned to 256-byte boundary
struct alignas(256) sse_t
{
    float sse_data[4];
};

// the array "cacheline" will be aligned to 128-byte boundary
alignas(128) char cacheline[128];


TEST(Keyword, AlignAs)
{
    sse_t x, y, z;
    struct default_aligned { float data[4]; } a, b, c;

    std::cout << "alignof(struct_float) = " << alignof(struct_float) << '\n'
			  << "alignof(sse_t) = "        << alignof(sse_t) << '\n'
			  << "alignof(char[128]) = "
			  << alignof(char[128]) << "\n\n";

    std::cout << std::hex << std::showbase
        << "&x: " << &x << '\n'
        << "&y: " << &y << '\n'
        << "&z: " << &z << '\n'
        << "&a: " << &a << '\n'
        << "&b: " << &b << '\n'
        << "&c: " << &c << '\n';
}

//extern "C" int func();
// the definition of func is written in assembly language
// raw string literal could be very useful
//__asm {R"(
//.globl func
//    .type func, @function
//    func:
//    .cfi_startproc
//    movl $7, %eax
//    ret
//    .cfi_endproc)"};
//
//TEST(Keyword, Asm)
//{
//    int n = func();
//    // extended inline assembly
//    __asm {"leal (%0,%0,4),%0"
//    : "=r" (n)
//        : "0" (n)};
//    std::cout << "7*5 = " << n << std::endl; // flush is intentional
//
//    // standard inline assembly
//    __asm {"movq $60, %rax\n\t" // the exit syscall number on Linux
//    "movq $2,  %rdi\n\t" // this program returns 2
//        "syscall"};
//}

TEST(Keyword, TransMem)
{
	//https://en.cppreference.com/w/cpp/language/transactional_memory
	//synchronized 
	//atomic_noexcept 
	//transaction_safe 
	//[[optimize_for_synchronized]]
	//
	//
}

TEST(Keyword, StorageDuration)
{
    //https://en.cppreference.com/w/cpp/language/storage_duration
}

TEST(Keyword, StructBindDecl)
{
    //https://en.cppreference.com/w/cpp/language/structured_binding
    int a[2] = { 1,2 };

    auto [x, y] = a; // creates e[2], copies a into e, then x refers to e[0], y refers to e[1]
    auto& [xr, yr] = a; // xr refers to a[0], yr refers to a[1]
    a[0] = 3;
    a[1] = 4;
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
    EXPECT_EQ(xr, 3);
    EXPECT_EQ(yr, 4);

    float xt{};
    char  yt{};
    int   zt{};

    std::tuple<float&, char&&, int> tpl(xt, std::move(yt), zt);
    const auto& [at, bt, ct] = tpl;
	
}

struct A { double x; };
const A* a;

decltype(a->x) y;       // type of y is double (declared type)
decltype((a->x)) z = y; // type of z is const double& (lvalue expression)

template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) // return type depends on template parameters
                                      // return type can be deduced since C++14
{
    return t + u;
}

TEST(Keyword, Decltype)
{
    int i = 33;
    decltype(i) j = i * 2;

    std::cout << "i and j are the same type? " << std::boolalpha
        << std::is_same_v<decltype(i), decltype(j)> << '\n';

    std::cout << "i = " << i << ", "
        << "j = " << j << '\n';

    auto f = [](int a, int b) -> int
    {
        return a * b;
    };

    decltype(f) g = f; // the type of a lambda function is unique and unnamed
    i = f(2, 2);
    j = g(3, 3);
    
    std::cout << "i = " << i << ", "
        << "j = " << j << '\n';
}

class Base {};

class Child1 : public virtual Base{};

class Child2 : public virtual Base{};

class GrandChild : public Child1, public Child2 {};


TEST(Keyword, VirtualClass)
{
    std::vector<GrandChild> grands;
    //std::vector<Base> bases = grands; //error E0312
    std::vector<Base> bases;
    for (auto grand_child : grands)
    {
        bases.push_back(grand_child);
    }
}