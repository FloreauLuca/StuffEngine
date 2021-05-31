cmake_minimum_required(VERSION 3.19)
project(Stuff)

message(STATUS "Initialization of the StuffEngine...")

# Sets paths
set_property(GLOBAL PROPERTY USE_FOLDERS On)
set(CORE_DIR "${CMAKE_SOURCE_DIR}/core" CACHE INTERNAL "Core folder")
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/externals" CACHE INTERNAL "Externals folder")
set(MAIN_DIR "${CMAKE_SOURCE_DIR}/main" CACHE INTERNAL "Main folder")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/main/test" CACHE INTERNAL "Tests folder")


# Librairies implementations
set(SFML_DIR "${EXTERNAL_DIR}/SFML-2.5.1/lib/cmake/SFML" CACHE STRING "")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Core files
include_directories("${CORE_DIR}/include")
add_subdirectory(${CORE_DIR})

# Test files
file(GLOB_RECURSE TEST_SRC ${TEST_DIR}/src/*.cpp ${TEST_DIR}/include/*.h)
source_group("Tests"				FILES ${TEST_SRC})
add_library(Tests STATIC ${TEST_SRC})
target_include_directories(Tests PUBLIC ${TEST_DIR}/include/)
target_link_libraries(Tests Core)

# Main files
file(GLOB_RECURSE main_src ${MAIN_DIR}/main.cpp)

add_executable(Main ${main_src})
target_link_libraries(Main PUBLIC Core Tests)

message(STATUS "StuffEngine ready to done some weird stuffs.")