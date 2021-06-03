cmake_minimum_required(VERSION 3.19)
project(Stuff)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Initialization of the StuffEngine...")

# Sets paths
set_property(GLOBAL PROPERTY USE_FOLDERS On)
set(COMMON_DIR "${CMAKE_SOURCE_DIR}/common" CACHE INTERNAL "Common folder")
set(CORE_DIR "${CMAKE_SOURCE_DIR}/core" CACHE INTERNAL "Core folder")
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/externals" CACHE INTERNAL "Externals folder")
set(MAIN_DIR "${CMAKE_SOURCE_DIR}/main" CACHE INTERNAL "Main folder")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/main/test" CACHE INTERNAL "Tests folder")
set(GTEST_DIR "${CMAKE_SOURCE_DIR}/main/gtests" CACHE INTERNAL "GTests folder")
set(BENCH_DIR "${CMAKE_SOURCE_DIR}/main/benchmarks" CACHE INTERNAL "Benchmarks folder")


# Librairies implementations
set(SFML_DIR "${EXTERNAL_DIR}/SFML-2.5.1/lib/cmake/SFML" CACHE STRING "")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "")
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "")
set(GOOGLE_BENCH_DIR "${EXTERNAL_DIR}/benchmark-1.5.4" CACHE STRING "")
add_subdirectory(${GOOGLE_BENCH_DIR})
# add_subdirectory("benchmark/")
set_target_properties(benchmark PROPERTIES FOLDER Externals/GTest)
set_target_properties(benchmark_main PROPERTIES FOLDER Externals/GTest)

set(GOOGLE_TEST_DIR ${EXTERNAL_DIR}/googletest-1.10.0)
set(BUILD_GMOCK OFF CACHE INTERNAL "")
set(INSTALL_GTEST OFF CACHE INTERNAL "")
add_subdirectory(${GOOGLE_TEST_DIR})

set_target_properties(gtest PROPERTIES FOLDER Externals/GTest)
set_target_properties(gtest_main PROPERTIES FOLDER Externals/GTest)


# Core files
include_directories("${CORE_DIR}/include")
add_subdirectory(${CORE_DIR})

#Common libs
add_subdirectory("common/algo_lib")

# GTests files
enable_testing()
file(GLOB_RECURSE GTEST_SRC ${GTEST_DIR}/*.cpp)
source_group("GTests" FILES ${GTEST_SRC})
add_executable(GTests ${GTEST_SRC})
target_link_libraries(GTests Core Algo_lib gtest gtest_main)
set_target_properties (GTests PROPERTIES FOLDER Test)

# Benchmark files
file(GLOB_RECURSE BENCH_SRC ${BENCH_DIR}/*.cpp)
add_executable(Benchmarks ${BENCH_SRC})
target_link_libraries(Benchmarks Core Algo_lib benchmark benchmark_main)
set_target_properties (Benchmarks PROPERTIES FOLDER Test)

# Test files
file(GLOB_RECURSE TEST_SRC ${TEST_DIR}/src/*.cpp ${TEST_DIR}/include/*.h)
source_group("Tests" FILES ${TEST_SRC})
add_library(Tests STATIC ${TEST_SRC})
target_include_directories(Tests PUBLIC ${TEST_DIR}/include/)
target_link_libraries(Tests Core Algo_lib)
set_target_properties (Tests PROPERTIES FOLDER Test)

# Main files
file(GLOB_RECURSE main_src ${MAIN_DIR}/main.cpp)

add_executable(Main ${main_src})
target_link_libraries(Main PUBLIC Core Tests Algo_lib)

message(STATUS "StuffEngine ready to done some weird stuffs.")