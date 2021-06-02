file(GLOB_RECURSE algo_lib_src include/*.h src/*.cpp)

add_library(Algo_lib STATIC ${algo_lib_src})
target_link_libraries(Algo_lib PUBLIC Core)
target_include_directories(Algo_lib PUBLIC "include/")
set_target_properties (Algo_lib PROPERTIES FOLDER Common)

