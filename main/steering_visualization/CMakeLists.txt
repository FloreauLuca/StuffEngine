include_directories("include/")

file(GLOB_RECURSE steering_visualization_src include/*.h src/*.cpp)

add_executable(steering_visualization ${steering_visualization_src})

target_link_libraries(steering_visualization PUBLIC core algo_lib)
set_target_properties (steering_visualization PROPERTIES FOLDER Main)