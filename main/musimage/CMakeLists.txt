include_directories("include/")

file(GLOB_RECURSE musimage_src include/*.h src/*.cpp)

add_executable(musimage ${musimage_src})

target_link_libraries(musimage PUBLIC core algo_lib)
set_target_properties (musimage PROPERTIES FOLDER Main)