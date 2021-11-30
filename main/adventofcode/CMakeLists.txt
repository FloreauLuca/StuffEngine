include_directories("include/")

file(GLOB_RECURSE adventofcode_src include/*.h src/*.cpp)

add_executable(adventofcode ${adventofcode_src})

target_link_libraries(adventofcode PUBLIC core)
set_target_properties (adventofcode PROPERTIES FOLDER Main)