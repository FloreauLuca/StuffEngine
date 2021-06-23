include_directories("include/")

file(GLOB_RECURSE search_visualization_src include/*.h src/*.cpp)

add_executable(search_visualization ${search_visualization_src})

target_link_libraries(search_visualization PUBLIC core algo_lib)
set_target_properties (search_visualization PROPERTIES FOLDER Main)