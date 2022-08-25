include_directories("include/")

file(GLOB_RECURSE midi_test_src include/*.h src/*.cpp)

add_executable(midi_test ${midi_test_src})

target_link_libraries(midi_test PUBLIC core algo_lib libParser)
set_target_properties (midi_test PROPERTIES FOLDER Main)