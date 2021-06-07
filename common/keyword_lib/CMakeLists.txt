file(GLOB_RECURSE keyword_lib_src include/*.h src/*.cpp)

add_library(keyword_lib STATIC ${keyword_lib_src})
target_link_libraries(keyword_lib PUBLIC core)
target_include_directories(keyword_lib PUBLIC "include/")
set_target_properties (keyword_lib PROPERTIES FOLDER Common)

