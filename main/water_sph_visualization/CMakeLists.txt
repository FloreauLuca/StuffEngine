include_directories("include/")

file(GLOB_RECURSE water_sph_visualization_src include/*.h src/*.cpp)

add_executable(water_sph_visualization ${water_sph_visualization_src})

target_link_libraries(water_sph_visualization PUBLIC core algo_lib)
set_target_properties (water_sph_visualization PROPERTIES FOLDER Main)