file(GLOB_RECURSE algo_lib_src include/*.h src/*.cpp)

add_library(algo_lib STATIC ${algo_lib_src})
target_link_libraries(algo_lib PUBLIC core)
target_include_directories(algo_lib PUBLIC "include/")
set_target_properties (algo_lib PROPERTIES FOLDER Common)

