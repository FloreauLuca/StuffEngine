include_directories("include/")

file(GLOB_RECURSE opengl_test_src include/*.h src/*.cpp)

add_executable(opengl_test ${opengl_test_src})

target_link_libraries(opengl_test PUBLIC core)
set_target_properties (opengl_test PROPERTIES FOLDER Main)