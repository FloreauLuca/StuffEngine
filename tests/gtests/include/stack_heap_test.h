#include "gtest/gtest.h"
#include <iostream>

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
    default:;
    }
}

void InitMemSlot()
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
}