include_directories("include/")

file(GLOB_RECURSE wave_function_collapse_src include/*.h src/*.cpp)

add_executable(wave_function_collapse ${wave_function_collapse_src})

target_link_libraries(wave_function_collapse PUBLIC core)
set_target_properties (wave_function_collapse PROPERTIES FOLDER Main)