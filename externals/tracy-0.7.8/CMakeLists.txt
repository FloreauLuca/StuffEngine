include_directories("${TRACY_BENCH_DIR}")

file(GLOB_RECURSE TRACY_SRC TracyClient.cpp Tracy.hpp)

add_compile_definitions(TRACY_ENABLE)
add_library(tracy STATIC ${TRACY_SRC})
target_include_directories(tracy PUBLIC "${TRACY_BENCH_DIR}")
