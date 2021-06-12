include_directories("include/")

file(GLOB_RECURSE sfml_test_src include/*.h src/*.cpp)

add_executable(sfml_test ${sfml_test_src})

target_link_libraries(sfml_test PUBLIC core)
set_target_properties (sfml_test PROPERTIES FOLDER Main)