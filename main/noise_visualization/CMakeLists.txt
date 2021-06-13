include_directories("include/")

file(GLOB_RECURSE noise_visualization_src include/*.h src/*.cpp)

add_executable(noise_visualization ${noise_visualization_src})

target_link_libraries(noise_visualization PUBLIC core algo_lib)
set_target_properties (noise_visualization PROPERTIES FOLDER Main)