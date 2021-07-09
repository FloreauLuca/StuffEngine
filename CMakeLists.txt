cmake_minimum_required(VERSION 3.17)
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
set(GTEST_DIR "${CMAKE_SOURCE_DIR}/tests/gtests" CACHE INTERNAL "GTests folder")
set(BENCH_DIR "${CMAKE_SOURCE_DIR}/tests/benchmarks" CACHE INTERNAL "Benchmarks folder")


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

set(TRACY_ENABLE ON CACHE BOOL "")
if(TRACY_ENABLE)
	set(TRACY_BENCH_DIR "${EXTERNAL_DIR}/tracy-0.7.8" CACHE STRING "")
	add_subdirectory(${TRACY_BENCH_DIR})
	set_target_properties(tracy PROPERTIES FOLDER Externals)
	add_compile_definitions(TRACY_ENABLE)
endif()

# Core files
include_directories("${CORE_DIR}/include")
add_subdirectory(${CORE_DIR})

#Common libs
add_subdirectory("common/algo_lib")
add_subdirectory("common/keyword_lib")

# GTests files
include(CTest)
enable_testing()
file(GLOB_RECURSE GTEST_SRC ${GTEST_DIR}/src/*.cpp  ${GTEST_DIR}/include/*.h)
include_directories("${GTEST_DIR}/include/")
add_executable(gtests ${GTEST_SRC})
add_test(NAME gtests COMMAND gtests)
target_link_libraries(gtests core algo_lib gtest gtest_main)
set_target_properties (gtests PROPERTIES FOLDER Test)

# Benchmark files
file(GLOB_RECURSE BENCH_FILES ${BENCH_DIR}/*.cpp)
foreach(bench_file ${BENCH_FILES} )
    file(RELATIVE_PATH bench_relative_path ${BENCH_DIR} ${bench_file})
    string( REPLACE ".cpp" "" bench_name ${bench_relative_path} )
	add_executable(${bench_name} ${bench_file})
	target_link_libraries(${bench_name} core algo_lib benchmark benchmark_main)
	set_target_properties (${bench_name} PROPERTIES FOLDER Test/Benchmarks)
endforeach ()

# Main files
file(GLOB MAIN_PROJECTS "${MAIN_DIR}/*")
foreach (MAIN_PROJECT_PATH ${MAIN_PROJECTS})
    get_filename_component(MAIN_PROJECT_NAME ${MAIN_PROJECT_PATH} NAME)

    message(VERBOSE "${MAIN_PROJECT_NAME} found at: '${MAIN_PROJECT_PATH}'")
    set(${MAIN_PROJECT_NAME} ON CACHE BOOL "")
    if (${MAIN_PROJECT_NAME})
        add_subdirectory(${MAIN_PROJECT_PATH})
    endif ()
endforeach ()

message(STATUS "StuffEngine ready to done some weird stuffs.")