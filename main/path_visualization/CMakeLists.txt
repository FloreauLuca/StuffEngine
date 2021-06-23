include_directories("include/")

file(GLOB_RECURSE path_visualization_src include/*.h src/*.cpp)

add_executable(path_visualization ${path_visualization_src})

target_link_libraries(path_visualization PUBLIC core algo_lib)
set_target_properties (path_visualization PROPERTIES FOLDER Main)