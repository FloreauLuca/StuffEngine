include_directories("include/")

file(GLOB_RECURSE sort_visualization_src include/*.h src/*.cpp)

add_executable(sort_visualization ${sort_visualization_src})

target_link_libraries(sort_visualization PUBLIC core algo_lib)
set_target_properties (sort_visualization PROPERTIES FOLDER Main)